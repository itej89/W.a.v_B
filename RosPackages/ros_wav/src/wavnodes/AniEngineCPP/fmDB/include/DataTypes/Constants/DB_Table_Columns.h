#pragma once

#include <map>
#include <string>

using std::map;
using std::string;

namespace fmDB
{

class DB_Table_Columns
{
public:
    enum DBTables
    {
        NO_DATA, //Used to indicate a table that is not present oin DB
        SERVO_DATA,
        SERVO_TURN,
        SERVO_LIFT,
        SERVO_LEAN,
        SERVO_TILT,
        CAPTURED_COMMANDS,
        EXPRESSIONS,
        ACTS,
        BEATS,
        CONTEXT,
        MACHINE_POSITIONS,
        TRACK
    };

    const map<DBTables, string> toString = {
        {NO_DATA, "NO_DATA"},
        {SERVO_DATA, "SERVO_DATA"},
        {SERVO_TURN, "SERVO_TURN"},
        {SERVO_LIFT, "SERVO_LIFT"},
        {SERVO_LEAN, "SERVO_LEAN"},
        {SERVO_TILT, "SERVO_TILT"},
        {CAPTURED_COMMANDS, "CAPTURED_COMMANDS"},
        {EXPRESSIONS, "EXPRESSIONS"},
        {ACTS, "ACTS"},
        {BEATS, "BEATS"},
        {CONTEXT, "CONTEXT"},
        {MACHINE_POSITIONS, "MACHINE_POSITIONS"},
        {TRACK, "TRACK"}};

    enum DBCONTEXT_KEYS
    {
        ACT_ID,
        BEAT_ID
    };

    enum COLUMN_TYPES
    {
        TEXT,
        NUMBER,
        FLOAT,
        BLOB
    };

    class CONTEXT_COLUMNS
    {
        public:
            enum etype
            {
                KEY = 0,
                VALUE = 1
            };

            etype value = KEY;

            CONTEXT_COLUMNS(){}
            CONTEXT_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {KEY, "KEY"},
                {VALUE, "VALUE"}
                };

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {KEY, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {VALUE, DB_Table_Columns::COLUMN_TYPES::TEXT}
            };
    };

    class MACHINE_POSITIONS_COLUMNS
    {
        public:
            enum etype
            {
                NAME = 0,
                TURN = 1,
                LIFT = 2,
                LEAN = 3,
                TILT = 4
            };

            etype value = NAME;
            MACHINE_POSITIONS_COLUMNS(){}
            MACHINE_POSITIONS_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {NAME, "NAME"},
                {TURN, "TURN"},
                {LIFT, "LIFT"},
                {LEAN, "LEAN"},
                {TILT, "TILT"}
                };

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {TURN, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {LIFT, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {LEAN, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {TILT, DB_Table_Columns::COLUMN_TYPES::NUMBER}
            };
    };

    class SERVO_DATA_COLUMNS
    {
        public:
            enum etype
            {
                ID = 0,
                NAME = 1,
                ADDRESS = 2,
                MIN_ANGLE = 3,
                MAX_ANGLE = 4
            };

            etype value = NAME;
            SERVO_DATA_COLUMNS(){}
            SERVO_DATA_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {NAME, "NAME"},
                {ADDRESS, "ADDRESS"},
                {MIN_ANGLE, "MIN_ANGLE"},
                {MAX_ANGLE, "MAX_ANGLE"}
                };

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {ADDRESS, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {MIN_ANGLE, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {MAX_ANGLE, DB_Table_Columns::COLUMN_TYPES::NUMBER}
            };
    };

    class SERVO_CALIBRATION_COLUMNS
    {
        public:
            enum etype
            {   ID = 0,
                DEGREE = 1,
                ADC = 2
            };

            etype value = DEGREE;
            SERVO_CALIBRATION_COLUMNS(){}
            SERVO_CALIBRATION_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {DEGREE, "DEGREE"},
                {ADC, "ADC"}};

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {DEGREE, DB_Table_Columns::COLUMN_TYPES::NUMBER},
                {ADC, DB_Table_Columns::COLUMN_TYPES::NUMBER}
            };
    };

    class CAPTURED_COMMAND_COLUMNS
    {
        public:
            enum etype
            {
                ID = 0,
                NAME = 1,
                COMMAND = 2
            };

            int value;
            CAPTURED_COMMAND_COLUMNS(){}
            CAPTURED_COMMAND_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {NAME, "NAME"},
                {COMMAND, "COMMAND"}};



            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {COMMAND, DB_Table_Columns::COLUMN_TYPES::TEXT}
            };
    };

    class EXPRESSIONS_COLUMNS
    {
        public:
            enum etype
            {
                ID = 0,
                NAME = 1,
                ACTION_DATA = 2,
                JOY = 3,
                SURPRISE = 4,
                FEAR = 5,
                SADNESS = 6,
                ANGER = 7,
                DISGUST = 8
            };

            int value;
            EXPRESSIONS_COLUMNS(){}
            EXPRESSIONS_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {ID, "ID"},
                {NAME, "NAME"},
                {ACTION_DATA, "ACTION_DATA"},
                {JOY, "JOY"},
                {SURPRISE, "SURPRISE"},
                {FEAR, "FEAR"},
                {SADNESS, "SADNESS"},
                {ANGER, "ANGER"},
                {DISGUST, "DISGUST"}};

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {ACTION_DATA, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {JOY, DB_Table_Columns::COLUMN_TYPES::FLOAT},
                {SURPRISE, DB_Table_Columns::COLUMN_TYPES::FLOAT},
                {FEAR, DB_Table_Columns::COLUMN_TYPES::FLOAT},
                {SADNESS, DB_Table_Columns::COLUMN_TYPES::FLOAT},
                {ANGER, DB_Table_Columns::COLUMN_TYPES::FLOAT},
                {DISGUST, DB_Table_Columns::COLUMN_TYPES::FLOAT}
            };
    };

    class ANIMATION_ACT_COLUMNS
    {
        public:
            enum etype
            {
                ID = 0,
                NAME = 1,
                SEQUENCE = 2
            };

            int Value;
            ANIMATION_ACT_COLUMNS(){}
            ANIMATION_ACT_COLUMNS(int value)
            {
                Value = value;
            }

            int getValue()
            {
                return Value;
            }

            const map<etype, string> toString = {
                {NAME, "NAME"},
                {SEQUENCE, "SEQUENCE"}
                };

            const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
                {NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
                {SEQUENCE, DB_Table_Columns::COLUMN_TYPES::TEXT}
            };
    };

    class ACTS_COLUMNS
    {
    public:
        enum etype
        {
            ACT_ID = 0,
            ACT_NAME = 1,
            ACT_AUDIO = 2
        };

        int Value;
        ACTS_COLUMNS(){}
        ACTS_COLUMNS(int value)
        {
            Value = value;
        }

        int getValue()
        {
            return Value;
        }

        const map<etype, string> toString = {
            {ACT_ID, "ACT_ID"},
            {ACT_NAME, "ACT_NAME"},
            {ACT_AUDIO, "ACT_AUDIO"}
            };

        const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
            {ACT_ID, DB_Table_Columns::COLUMN_TYPES::NUMBER},
            {ACT_NAME, DB_Table_Columns::COLUMN_TYPES::TEXT},
            {ACT_AUDIO, DB_Table_Columns::COLUMN_TYPES::TEXT}
        };

    };

    class TRACK_COLUMNS
    {
        public:
            enum etype
            {
                TRACK_ID = 0,
                DATA = 1
            };

            int value;
            TRACK_COLUMNS(){}
            TRACK_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {TRACK_ID, "TRACK_ID"},
                {DATA, "DATA"}
                };

        const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
            {TRACK_ID, DB_Table_Columns::COLUMN_TYPES::NUMBER},
            {DATA, DB_Table_Columns::COLUMN_TYPES::BLOB}
        };
    };

    class BEATS_COLUMNS
    {
        public:
            enum etype
            {
                BEAT_ID = 0,
                ACT_ID = 1,
                ACTION_DATA = 2,
                JOY = 3,
                SURPRISE = 4,
                FEAR = 5,
                SADNESS = 6,
                ANGER = 7,
                DISGUST = 8,
                StartSec = 9,
                EndSec = 10
            };

            int value;
            BEATS_COLUMNS(){}
            BEATS_COLUMNS(int value)
            {
                value = value;
            }

            int getValue()
            {
                return value;
            }

            const map<etype, string> toString = {
                {BEAT_ID, "BEAT_ID"},
                {ACT_ID, "ACT_ID"},
                {ACTION_DATA, "ACTION_DATA"},
                {JOY, "JOY"},
                {SURPRISE, "SURPRISE"},
                {FEAR, "FEAR"},
                {SADNESS, "SADNESS"},
                {ANGER, "ANGER"},
                {DISGUST, "DISGUST"},
                {StartSec, "StartSec"},
                {EndSec, "EndSec"}
                };

        const map<etype, DB_Table_Columns::COLUMN_TYPES> typeOf = {
            {BEAT_ID, DB_Table_Columns::COLUMN_TYPES::NUMBER},
            {ACT_ID, DB_Table_Columns::COLUMN_TYPES::NUMBER},
            {ACTION_DATA, DB_Table_Columns::COLUMN_TYPES::TEXT},
            {JOY, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {SURPRISE, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {FEAR, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {SADNESS, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {ANGER, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {DISGUST, DB_Table_Columns::COLUMN_TYPES::FLOAT},
            {StartSec, DB_Table_Columns::COLUMN_TYPES::NUMBER},
            {EndSec, DB_Table_Columns::COLUMN_TYPES::NUMBER}
        };
    };
};
} // namespace fmDB