#pragma once






#include <vector>
#include <iterator>
#include <string>

#include <sqlite3.h>

#include "DataTypes/Column_Definition.h"



using std::string;
using std::vector;

namespace fmDB
{
class DB_Basic_Operations
{

private:
    //string DB_PATH = "/home/tej/Documents/AniClientCpp";
    string DB_PATH = "/data/data/org.godotengine.hightspeedfeeling/databases";

    string DB_NAME = "CommandStore.db";

    sqlite3 *SQLDataBase;
    char *zErrMsg = 0;
    int rc = SQLITE_INTERNAL;

    string databasePath;

    string FullDBPath = "";

public:
    //The Android's default system path of your application database.

    string GetDBDirectoryPath()
    {
        return DB_PATH;
    }

    string GetDBPath()
    {
        return FullDBPath;
    }

    DB_Basic_Operations()
    {

        FullDBPath = DB_PATH + "/" + DB_NAME;

        databasePath = GetDBPath();
    }

    DB_Basic_Operations(string DBPath)
    {

        FullDBPath = DBPath;
        databasePath = GetDBPath();
    }

    bool IsOpen()
    {
        if (rc != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    static int callback(void *data, int argc, char **argv, char **azColName)
    {
        vector<vector<string>> * DataTable = static_cast<std::vector<vector<string>> *>( data );
        vector<string> row(argv, argv+argc);
        DataTable->push_back(row);
        return 0;
    }

    bool InitializeDB()
    {
        rc = sqlite3_open(databasePath.c_str(), &SQLDataBase);
        //printf("DB Path : %s\n", databasePath.c_str());
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "InitializeDB - SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        }
        
        else
        {
            //fprintf(stdout, "InitializeDB successfully\n");
            return true;
        }
    }

    string ErrorMessage;

    bool CreateTable(string TableName, vector<Column_Definition> Columns)
    {

        try
        {
            if (SQLDataBase == nullptr)
            {
                ErrorMessage = ("Error: DB Null");
                return false;
            }

            if (IsOpen())
            {

                string sql_stmt = "CREATE TABLE IF NOT EXISTS " + TableName + " (ID INTEGER PRIMARY KEY AUTOINCREMENT";

                for (Column_Definition &column : Columns)
                {
                    sql_stmt += ", " + column.ColumnName + " " + column.ColumnType;
                }

                sql_stmt += ")";

                rc = sqlite3_exec(SQLDataBase, sql_stmt.c_str(), callback, 0, &zErrMsg);

                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                    return false;
                }
                else
                {
                    //fprintf(stdout, "Table created successfully\n");
                    return true;
                }
            }
            else
            {
                ErrorMessage = ("Error: Unable to Open DB");
                return false;
            }

            return true;
        }
        catch (...)
        {
            ErrorMessage = ("Error: Unable to Open DB");
            return false;
        }
    }

    bool EmptyTable(string TableName)
    {

        try
        {
            //CommandStoreDB = SQLiteDatabase.openDatabase(databasePath, null, SQLiteDatabase.OPEN_READWRITE);
            if (IsOpen())
            {

                string insertSQL = "DELETE FROM " + TableName;
                rc = sqlite3_exec(SQLDataBase, insertSQL.c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                     return false;
                }
                else
                {
                    //fprintf(stdout, "Table emptied successfully\n");
                    return true;
                }
                // CloseDBConnection();
            }
            else
            {
                ErrorMessage = "Error: Unable to Open DB";
                return false;
            }
            return true;
        }
        catch (...)
        {
            ErrorMessage = ("Error: Unable to EmptyTable");
            return false;
        }
    }

    
    vector<vector<string>>* ReadDataFromTable(string SqlQuery)
    {

            vector<vector<string>>  *cursor = new vector<vector<string>>();
        try
        {
            // CommandStoreDB = SQLiteDatabase.openDatabase(databasePath, null, SQLiteDatabase.OPEN_READWRITE);
            if (IsOpen())
            {
                
                 rc = sqlite3_exec(SQLDataBase, SqlQuery.c_str(), callback, cursor, &zErrMsg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                     return cursor;
                }
                else
                {
                    //fprintf(stdout, "Table read successful\n");
                    return cursor;
                }

                
            }
            else
            {
                ErrorMessage = "Error: Unable to Open DB";
                return cursor;
            }
        }
        catch (...)
        {
            ErrorMessage = ("Error: Unable to ReadDataFromTable");
            return cursor;
        }
    }

    void CloseDBConnection()
    {
        if (IsOpen())
        {
            rc = 0;
            sqlite3_close(SQLDataBase);
        }
    }

    // long InsertContentValueToTable(string Table_Name, ContentValues values)
    // {
    //     long ID = -1;
    //     try
    //     {
    //         //  CommandStoreDB = SQLiteDatabase.openDatabase(databasePath, null, SQLiteDatabase.OPEN_READWRITE);
    //         if (IsOpen())
    //         {

    //             ID = SQLDataBase.insert(Table_Name, null, values);
    //         }
    //         // CloseDBConnection();
    //         return ID;
    //     }
    //     catch (...)
    //     {
    //         ErrorMessage = ("Error: Unable to ExecuteSqlCommand");
    //         return ID;
    //     }
    // }

    bool ExecuteSqlCommand(string SqlQuery)
    {
        try
        {
            //  CommandStoreDB = SQLiteDatabase.openDatabase(databasePath, null, SQLiteDatabase.OPEN_READWRITE);
            if (IsOpen())
            {

                rc = sqlite3_exec(SQLDataBase, SqlQuery.c_str(), callback, 0, &zErrMsg);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "SQL error: %s\n", zErrMsg);
                    sqlite3_free(zErrMsg);
                     return false;
                }
                else
                {
                   // fprintf(stdout, "Table created successfully\n");
                     return true;
                }
            }
            // CloseDBConnection();
           
        }
        catch (...)
        {
            ErrorMessage = ("Error: Unable to ExecuteSqlCommand");
            return false;
        }
    }

};
} // namespace fmDB