#pragma once

#include <vector>
#include <map>
#include <iterator>
#include <string>
#include<iostream> 
#include <memory>
#include <utility>
#include <sqlite3.h>


#include "DataTypes/Constants/DB_Table_Columns.h"
#include "DataTypes/ACTS.h"
#include "DataTypes/Beats_Type.h"
#include "DataTypes/Captured_Command_Type.h"
#include "DataTypes/Column_Definition.h"
#include "DataTypes/DataContext.h"
#include "DataTypes/Expressions_Type.h"
#include "DataTypes/Machine_Position_Type.h"
#include "DataTypes/Servo_Calibration_Type.h"
#include "DataTypes/Servo_Data_Type.h"
#include "DataTypes/Track.h"
#include "DB_Basic_Operations.h"

using std::string;
using std::vector;
using std::map;


namespace fmDB
{



         static __inline__ double atof(const char *nptr)
    {
        return (strtod(nptr, NULL));
    }

class DB_Local_Store
{
private:
    string APP_BASE_DB = "CommandStore.sqlite";

     map<string, std::unique_ptr<DB_Basic_Operations>>* DataBases = new map<string, std::unique_ptr<DB_Basic_Operations>>();

    string DBKey = "DEFAULT";

public:

    ~DB_Local_Store()
    {
        delete DataBases;
    }
    DB_Local_Store()
    {

        if (DataBases->find("DEFAULT") != DataBases->end() && DataBases->at("DEFAULT")->IsOpen())
        {
            return;
        }

        if (DataBases->find("DEFAULT") != DataBases->end())
        {
            DataBases->erase("DEFAULT");
        }
        DBKey = "DEFAULT";
        DataBases->insert( std::make_pair<string, std::unique_ptr<DB_Basic_Operations>>("DEFAULT", std::unique_ptr<DB_Basic_Operations>(new DB_Basic_Operations())));
       
       // PlaceDB(DataBases->at("DEFAULT"));
       
        DataBases->at("DEFAULT")->InitializeDB();
    }

    DB_Local_Store(string DBPath)
    {
        DBKey = DBPath;
        if (DataBases->find(DBPath) != DataBases->end() && DataBases->at(DBPath)->IsOpen())
        {
            return;
        }

        if (DataBases->find(DBPath) != DataBases->end())
        {
            DataBases->erase(DBPath);
        }

        DataBases->insert(std::make_pair<string, std::unique_ptr<DB_Basic_Operations>>(DBPath.c_str(), std::unique_ptr<DB_Basic_Operations>(new DB_Basic_Operations())));
        DataBases->at(DBPath)->InitializeDB();
    }

    void CloseDBConnection()
    {
        if (DataBases->find(DBKey) != DataBases->end())
        {
            if (DataBases->at(DBKey)->IsOpen())
                DataBases->at(DBKey)->CloseDBConnection();

            DataBases->erase(DBKey);
        }
    }

    // string RemoveDB(DB_Basic_Operations DB)
    // {
    //     string databasePath = DB.GetDBPath();

    //     File file = new File(databasePath);
    //     try
    //     {
    //         if (file.exists())
    //         {
    //             file.delete();
    //         }
    //     }
    //     catch (...)
    //     {
    //         return "Database deltetion failed!";
    //     }

    //     return "Database Removed Successfully!";
    // }

    // string PlaceDB(DB_Basic_Operations* DB)
    // {
    //     string databasePath = DB->GetDBPath();

    //     File dbDir = new File(DB.GetDBDirectoryPath());
    //     File dbFile = new File(databasePath);

    //     try
    //     {

    //         if (!dbFile.exists())
    //         {

    //             if (!dbDir.mkdirs())
    //             {
    //             }
    //             //Open your local db as the input stream
    //             InputStream myInput = context.getAssets().open(APP_BASE_DB);

    //             dbDir.createNewFile();
    //             //Open the empty db as the output stream
    //             OutputStream myOutput = new FileOutputStream(DB.GetDBPath(), false);

    //             //transfer bytes from the inputfile to the outputfile
    //             byte[] buffer = new byte[1024];
    //             int length;
    //             while ((length = myInput.read(buffer)) > 0)
    //             {
    //                 myOutput.write(buffer, 0, length);
    //             }

    //             //Close the streams
    //             myOutput.flush();
    //             myOutput.close();
    //             myInput.close();

    //         }
    //     }
    //     catch (...)
    //     {
    //         Log.d("Error", ex.getMessage());
    //     }

    //     return "Database Created Successfully!";
    // }

    int GetServoDegreeFromADC(DB_Table_Columns::DBTables TableName, int ADC)
    {
        fmDB::Servo_Calibration_Type DegreeData;

        DB_Table_Columns _DB_Table_Columns;
        vector<Servo_Calibration_Type> CalibratedData = ReadServoCalibrationData(_DB_Table_Columns.toString.at(TableName));

        if (CalibratedData.size() > 0)
        {
            if (CalibratedData.at(0).ADC > ADC)
            {
                DegreeData = CalibratedData.at(0);
            }
            else if (CalibratedData.at(CalibratedData.size() - 1).ADC < ADC)
            {
                DegreeData = CalibratedData.at(CalibratedData.size() - 1);
            }
            else
            {

                for (Servo_Calibration_Type Calibration : CalibratedData)
                {
                    if (Calibration.ADC >= ADC)
                    {
                        DegreeData = Calibration;
                        break;
                    }
                }
            }
        }
        else
        {
            return -1;
        }

        return (DegreeData.Degree);
    }

    Machine_Position_Type ReadMachinePositionByName(string name)
    {
        Machine_Position_Type machine_Position_Type("");

        vector<vector<string>> *ret = DataBases->at(DBKey)->ReadDataFromTable("SELECT " +
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::NAME)+ ", " + 
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TURN) + ", " + 
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LIFT) + ", " + 
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LEAN) + ", " + 
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TILT) + " from " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::MACHINE_POSITIONS) + " WHERE " + 
        (new DB_Table_Columns::MACHINE_POSITIONS_COLUMNS())->toString.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::NAME) + " = '" + name + "'");

        if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {
            string NAME = row.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::NAME);
            int TURN = atoi(row.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TURN).c_str());
            int LIFT = atoi(row.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LIFT).c_str());
            int LEAN = atoi(row.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::LEAN).c_str());
            int TILT = atoi(row.at(DB_Table_Columns::MACHINE_POSITIONS_COLUMNS::TILT).c_str());

            machine_Position_Type = Machine_Position_Type(NAME, TURN, LIFT, LEAN, TILT);
            }
        }

        //dbHelper.CloseDBConnection();
        delete ret;
        return machine_Position_Type;
    }

    vector<Servo_Calibration_Type> ReadServoCalibrationData(string TableName)
    {

        vector<Servo_Calibration_Type> CalibrationData;
        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName);

       if (ret->size() > 0)
       {
             for(vector<string> row: *ret)
            {
                CalibrationData.push_back(Servo_Calibration_Type(atoi(row.at(DB_Table_Columns::SERVO_CALIBRATION_COLUMNS::DEGREE).c_str()),
                                                               atoi(row.at(DB_Table_Columns::SERVO_CALIBRATION_COLUMNS::ADC).c_str())));

            }
        }
        //dbHelper.CloseDBConnection();
         delete ret;
        return CalibrationData;
    }

    vector<Captured_Command_Type> ReadCapturedCommands(string TableName)
    {
        vector<Captured_Command_Type> CommandData;
        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName);

        if (ret->size() > 0)
        {
            for(vector<string> row: *ret)
            {
                CommandData.push_back(Captured_Command_Type(row.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME),
                                                            row.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::COMMAND)));
            }
        }
        //dbHelper.CloseDBConnection();
         delete ret;
        return CommandData;
    }

    string LoadServoDataIntoDB(Servo_Data_Type Data)
    {
        string insertSQL = "INSERT INTO " + 
                           (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::SERVO_DATA) + " (" +
                           (new DB_Table_Columns::SERVO_DATA_COLUMNS())->toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::NAME) + ", " +
                           (new DB_Table_Columns::SERVO_DATA_COLUMNS())->toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::ADDRESS) + ", " +
                           (new DB_Table_Columns::SERVO_DATA_COLUMNS())->toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::MIN_ANGLE) + ", " +
                           (new DB_Table_Columns::SERVO_DATA_COLUMNS())->toString.at(DB_Table_Columns::SERVO_DATA_COLUMNS::MAX_ANGLE) +
                           ") VALUES ('(Data.Name)', '(Data.Address)', '(Data.Min_Angle)', '(Data.Max_Angle)')";

         bool  Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);
 
        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Servo Data Loaded Successfully.";
    }

    string _EmptyTable(string TableName)
    {
        bool Status = DataBases->at(DBKey)->EmptyTable(TableName);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Data deleted from Table.";
    }

    Captured_Command_Type ReadCommandByName(string name)
    {
        Captured_Command_Type Captured_Command_Data("", "");
         vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("SELECT " + (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME) + ", " +
                                                               "" + (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::COMMAND) + " from " + 
                                                               (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CAPTURED_COMMANDS) +
                                                               " WHERE " + (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME) + " = '" + 
                                                               name + "'");

        if (ret->size() > 0)
        {
            for(vector<string> row: *ret)
            {
                string CommandName = row.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME);
                string Command = row.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::COMMAND);
                Captured_Command_Data = Captured_Command_Type(CommandName, Command);
            }
        }
        // dbHelper.CloseDBConnection();
         delete ret;
        return Captured_Command_Data;
    }

    string DeleteCommandByName(string name)
    {
        string deleteQuery = "DELETE FROM " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CAPTURED_COMMANDS) + " WHERE " +
                             (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME) + " = '" + name + "'";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(deleteQuery);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Command Deleted Successfully!";
    }

    string saveCommand(Captured_Command_Type Data)
    {
        Captured_Command_Type Found_Command_Data = ReadCommandByName(Data.Name);
        if (Found_Command_Data.Name != "")
        {
            DeleteCommandByName(Found_Command_Data.Name);
        }

        string insertSQL = "INSERT INTO " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CAPTURED_COMMANDS) + " (" +
                           (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::NAME) + ", " +
                           (new DB_Table_Columns::CAPTURED_COMMAND_COLUMNS())->toString.at(DB_Table_Columns::CAPTURED_COMMAND_COLUMNS::COMMAND) +
                           ") VALUES ('" + Data.Name + "', '" + Data.Command + "')";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        //  dbHelper.CloseDBConnection();
        return "Command Data Saved Successfully!";
    }

    string saveCalibrationData(Servo_Calibration_Type Data)
    {

        string insertSQL = "INSERT INTO " + 
        Data.Name + " (" +
        (new DB_Table_Columns::SERVO_CALIBRATION_COLUMNS())->toString.at(DB_Table_Columns::SERVO_CALIBRATION_COLUMNS::ADC) + ", " +
        (new DB_Table_Columns::SERVO_CALIBRATION_COLUMNS())->toString.at(DB_Table_Columns::SERVO_CALIBRATION_COLUMNS::DEGREE) + 
        ") VALUES ('(Data.ADC)', '(Data.Degree)')";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);
         
        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        // dbHelper.CloseDBConnection();
        return "Calibration Data Saved Successfully!";
    }

    string saveInContext(DataContext Data)
    {

        vector<DataContext> ContextData = ReadFromContext(Data.KEY);

        if (ContextData.size() > 0)
        {
            DeleteFromContext(Data.KEY);
        }

        string insertSQL = "INSERT INTO " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CONTEXT) + " (" +
                           (new DB_Table_Columns::CONTEXT_COLUMNS())->toString.at(DB_Table_Columns::CONTEXT_COLUMNS::KEY) + ", " +
                           (new DB_Table_Columns::CONTEXT_COLUMNS())->toString.at(DB_Table_Columns::CONTEXT_COLUMNS::VALUE) +
                           ") VALUES ('" + Data.KEY + "', '" + Data.VALUE + "')";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Data Context Saved Successfully!";
    }

    string DeleteFromContext(string KEY)
    {

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand("delete from " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CONTEXT) + " WHERE " + 
        (new DB_Table_Columns::CONTEXT_COLUMNS())->toString.at(DB_Table_Columns::CONTEXT_COLUMNS::KEY) + " = '" + KEY + "'");

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Data Context delete Successful!";
    }

    vector<DataContext> ReadFromContext(string KEY)
    {

        vector<DataContext> ContextData;

        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("SELECT " + (new DB_Table_Columns::CONTEXT_COLUMNS())->toString.at(DB_Table_Columns::CONTEXT_COLUMNS::VALUE) + " from " + 
                                                                (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::CONTEXT) +
                                                               " WHERE " + (new DB_Table_Columns::CONTEXT_COLUMNS())->toString.at(DB_Table_Columns::CONTEXT_COLUMNS::KEY) + " = '" + KEY + "'");

        if (ret->size() > 0)
        {
            for(vector<string> row: *ret)
            {

                string rKEY = row.at(DB_Table_Columns::CONTEXT_COLUMNS::KEY);
                string rVALUE = row.at(DB_Table_Columns::CONTEXT_COLUMNS::VALUE);
                DataContext ContextRow(rKEY, rVALUE);
                ContextData.push_back(ContextRow);

            }
        }
        delete ret;
        return ContextData;
    }

    string saveAct(ACTS Data)
    {
        string insertSQL = "INSERT INTO " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::ACTS) + " (" +
                           (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_NAME) + ", " +
                           (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_AUDIO) +
                           ") VALUES ('" + (Data.Name) + "', '" + (Data.Audio) + "')";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Animation Act Saved Successfully!";
    }

    vector<ACTS> ReadActWithID(int ID)
    {

        vector<ACTS> ActsData;

        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::ACTS) + " WHERE " + 
                                                                    (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID) + " = '" + std::to_string(ID) + "'");

        if (ret->size() > 0)
        {
            for(vector<string> row: *ret)
            {

                string ActName = row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_NAME);
                string ActAudio = row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_AUDIO);
                ACTS ContextRow = ACTS(ActName, ID, ActAudio);
                ActsData.push_back(ContextRow);

            }
        }
         delete ret;
        return ActsData;
    }

    int GetLastActID()
    {
        int ID = -1;
        string selectSQL = "SELECT " + (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID) + " FROM " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::ACTS) + " ORDER BY " + 
        (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID) + " DESC LIMIT 1";

        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable(selectSQL);

        if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {

                ID = atoi(row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID).c_str());
                break;

            } 
        }
         delete ret;
        return ID;
    }

    string DeleteAct(int ID)
    {
        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand("DELETE from " +  (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::ACTS) + " WHERE " + 
        (new DB_Table_Columns::ACTS_COLUMNS())->toString.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID) + " = '" + std::to_string(ID) + "'");

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Deleted Expression Successfully.";
    }

    vector<ACTS> ReadActs(string TableName)
    {

        vector<ACTS> ActsData;
        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName);

        if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {

                string ActName = row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_NAME);
                int ActID = atoi(row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID).c_str());
                string Audio = row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_AUDIO);
                ACTS ContextRow =  ACTS(ActName, ActID, Audio);
                ActsData.push_back(ContextRow);

            } 
        }
        return ActsData;
    }

    int GetLastBeatID()
    {
        int ID = -1;
        string selectSQL = "SELECT " + (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID) + " FROM " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::BEATS) + " ORDER BY " + 
        (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID) + " DESC LIMIT 1";

        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable(selectSQL);

        if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {

                ID = atoi(row.at(DB_Table_Columns::ACTS_COLUMNS::ACT_ID).c_str());
                break;
            } 
        }
        delete ret;
        return ID;
    }

    string DeleteBeatByActID(int ACT_ID)
    {
        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand("DELETE from " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::BEATS) + " WHERE " + 
        (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::ACT_ID) + " = '" + std::to_string(ACT_ID) + "'");

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Deleted Expression Successfully.";
    }

    string DeleteBeatByBeatID(int BEAT_ID)
    {
        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand("DELETE from " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::BEATS) + " WHERE " + 
        (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID) + " = '" + std::to_string(BEAT_ID) + "'");

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Deleted Expression Successfully.";
    }

    string saveBeat(Beats_Type Data)
    {
        string insertSQL = "INSERT INTO " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::BEATS) + " (" +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::ACT_ID) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::ACTION_DATA) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::JOY) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::SURPRISE) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::FEAR) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::SADNESS) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::ANGER) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::DISGUST) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::StartSec) + ", " +
                           (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::EndSec) +
                           ") VALUES ('" + std::to_string(Data.Act_Id) + "', '" + Data.Action_Data + "', '" + std::to_string(Data.JOY) + "', '" + std::to_string(Data.SURPRISE) + "', '" + std::to_string(Data.FEAR) + "', '" + std::to_string(Data.SADNESS) + "', '" + std::to_string(Data.ANGER) + "', '" + std::to_string(Data.DISGUST) + "', '" + std::to_string(Data.StartSec) + "', '" + std::to_string(Data.EndSec) + "')";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Animation Act Saved Successfully!";
    }

    vector<Beats_Type> ReadBeatsByBeatID(string TableName, int BEAT_ID)
    {

        vector<Beats_Type> Beats;
       vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName + " WHERE " + 
       (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID) + " = '" + std::to_string(BEAT_ID) + "'");

       if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {


                int act_Id = atoi(row.at(DB_Table_Columns::BEATS_COLUMNS::ACT_ID).c_str());
                int beat_id = BEAT_ID;
                string action_Data = row.at(DB_Table_Columns::BEATS_COLUMNS::ACTION_DATA);
                float joy = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::JOY).c_str());
                float surprise = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::SURPRISE).c_str());
                float fear = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::FEAR).c_str());
                float sadness = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::SADNESS).c_str());
                float anger = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::ANGER).c_str());
                float disgust = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::DISGUST).c_str());
                int startSec = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::StartSec).c_str());
                int endSec = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::EndSec).c_str());

                Beats.push_back(Beats_Type(act_Id, beat_id, action_Data, joy, surprise, fear, sadness, anger, disgust, startSec, endSec));

            } 
        }

        return Beats;
    }

    Track ReadChoreogramTrack(string TableName)
    {

        Track audioTrack;
        // Cursor cursor = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName);

        // if (cursor.moveToFirst())
        // {
        //     do
        //     {
        //         int ID = cursor.getInt(cursor.getColumnIndex(DB_Table_Columns.TRACK_COLUMNS.TRACK_ID.toString()));
        //         byte[] track = cursor.getBlob(cursor.getColumnIndex(DB_Table_Columns.TRACK_COLUMNS.DATA.toString()));
        //         audioTrack = Track(ID, track);
        //         break;
        //     } while (cursor.moveToNext());
        // }

        // cursor.close();

        return audioTrack;
    }

    vector<Beats_Type> ReadBeatsByActID(string TableName, int ACT_ID)
    {

        vector<Beats_Type> Beats;
        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName + " WHERE " + 
        (new DB_Table_Columns::BEATS_COLUMNS())->toString.at(DB_Table_Columns::BEATS_COLUMNS::ACT_ID) + " = '" + std::to_string(ACT_ID) + "'");

        if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {

                int act_Id = ACT_ID;
                int beat_id = atoi(row.at(DB_Table_Columns::BEATS_COLUMNS::BEAT_ID).c_str());
                string action_Data = row.at(DB_Table_Columns::BEATS_COLUMNS::ACTION_DATA);
                float joy = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::JOY).c_str());
                float surprise = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::SURPRISE).c_str());
                float fear = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::FEAR).c_str());
                float sadness = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::SADNESS).c_str());
                float anger = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::ANGER).c_str());
                float disgust = atof(row.at(DB_Table_Columns::BEATS_COLUMNS::DISGUST).c_str());
                int startSec = atoi(row.at(DB_Table_Columns::BEATS_COLUMNS::StartSec).c_str());
                int endSec = atoi(row.at(DB_Table_Columns::BEATS_COLUMNS::EndSec).c_str());

                Beats.push_back(Beats_Type(act_Id, beat_id, action_Data, joy, surprise, fear, sadness, anger, disgust, startSec, endSec));

            }
        }
        delete ret;
        return Beats;
    }

    bool saveExpression(Expressions_Type Data)
    {
        string insertSQL = "INSERT INTO " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::EXPRESSIONS) + " (" +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::NAME) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ACTION_DATA) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::JOY) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SURPRISE) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::FEAR) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SADNESS) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ANGER) + ", " +
                           (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::DISGUST) +

                           ") VALUES ('" + Data.Name + "', '" + Data.Action_Data + "', " + 
                           std::to_string(Data.JOY) + ", " + std::to_string(Data.SURPRISE) + ", " + std::to_string(Data.FEAR) + ", " + 
                           std::to_string(Data.SADNESS) + ", " + std::to_string(Data.ANGER) + "," + std::to_string(Data.DISGUST) + ")";

        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand(insertSQL);

        // dbHelper.CloseDBConnection();

        if (!Status)
        {
            //return dbHelper.ErrorMessage;
            return false;
        }

        return true;

        //return "Expression Saved Successfully!";
    }

    Expressions_Type readExpression(string ByName)
    {
        Expressions_Type Saved_Action_Data("", "", (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0);

         vector<vector<string>>* ret =  DataBases->at(DBKey)->ReadDataFromTable("SELECT * from " +  (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::EXPRESSIONS) +
                                                               " WHERE " + 
                                                               (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::NAME) + " = '" + ByName + "'");

       if (ret->size() > 0)
        {
            for(vector<string> row : *ret)
            {

                string ActionName = row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::NAME);
                string ActionData =  row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ACTION_DATA);
                float Joy = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::JOY).c_str());
                float Surprise =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SURPRISE).c_str());
                float Fear =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::FEAR).c_str());
                float Anger = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ANGER).c_str());
                float Sadness =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SADNESS).c_str());
                float Disguest =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::DISGUST).c_str());
                Saved_Action_Data =  Expressions_Type(ActionName, ActionData, Joy, Surprise, Fear, Sadness, Anger, Disguest);
                break;
            } 
        }
        delete ret;
        return Saved_Action_Data;
    }

    Expressions_Type readExpressionByEmotion(float JOY, float SURPRISE, float FEAR, float ANGER, float SADNESS, float DISGUST)
    {

        Expressions_Type Saved_Action_Data("", "", (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0, (float)0.0);

         vector<vector<string>>* ret =  DataBases->at(DBKey)->ReadDataFromTable("SELECT * from " + (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::EXPRESSIONS) + 
        " order by ABS(JOY-" + std::to_string(JOY) + ") + ABS(ANGER-" + std::to_string(ANGER) + ") + ABS(DISGUST-" + std::to_string(DISGUST) + ") + ABS(SURPRISE-" + 
                               std::to_string(SURPRISE) + ") + ABS(SADNESS-" + std::to_string(SADNESS) + ") + ABS(FEAR-" + std::to_string(FEAR) + ") LIMIT 1");

        if (ret->size() > 0)
        {
                vector<string> row = ret->at(0);
                string ActionName = row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::NAME);
                string ActionData =  row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ACTION_DATA);
                float Joy = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::JOY).c_str());
                float Surprise =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SURPRISE).c_str());
                float Fear =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::FEAR).c_str());
                float Anger = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ANGER).c_str());
                float Sadness =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SADNESS).c_str());
                float Disguest =  atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::DISGUST).c_str());
            Saved_Action_Data =  Expressions_Type(ActionName, ActionData, Joy, Surprise, Fear, Sadness, Anger, Disguest);
        }
        delete ret;
        return Saved_Action_Data;
    }

    int GetLastEmotionID()
    {
        int ID = -1;
        string selectSQL = "SELECT " +   (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ID) + " FROM " + 
        (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::EXPRESSIONS) + " ORDER BY " +   
        (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ID) + " DESC LIMIT 1";

        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable(selectSQL);

        if (ret->size() > 0)
        {
                vector<string> row = ret->at(0);

            ID = atoi(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ID).c_str());
        }
        delete ret;
        return ID;
    }

    string DeleteExpression(int ID)
    {
        bool Status = DataBases->at(DBKey)->ExecuteSqlCommand("DELETE from " +  (new DB_Table_Columns())->toString.at(DB_Table_Columns::DBTables::EXPRESSIONS) + " WHERE " + 
         (new DB_Table_Columns::EXPRESSIONS_COLUMNS())->toString.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ID) + " = '" + std::to_string(ID) + "'");

        if (!Status)
        {
            return DataBases->at(DBKey)->ErrorMessage;
        }

        return "Deleted Expression Successfully.";
    }

    vector<Expressions_Type> ReadExpressions(string TableName)
    {

        vector<Expressions_Type> ExpressionsData;
        vector<vector<string>>* ret = DataBases->at(DBKey)->ReadDataFromTable("select * from " + TableName);

        if (ret->size() > 0)
        {
            for(vector<string> row: *ret)
            {
                int id = atoi(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ID).c_str());
                string name = row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::NAME);
                string action_Data = row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ACTION_DATA);
                float joy = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::JOY).c_str());
                float surprise = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SURPRISE).c_str());
                float fear = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::FEAR).c_str());
                float sadness = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::SADNESS).c_str());
                float anger = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::ANGER).c_str());
                float disgust = atof(row.at(DB_Table_Columns::EXPRESSIONS_COLUMNS::DISGUST).c_str());

                Expressions_Type Expression(id, name, action_Data, joy, surprise, fear, sadness, anger, disgust);
                ExpressionsData.push_back(Expression);
            }
        }

        delete ret;
        return ExpressionsData;
    }
};

} // namespace fmDB