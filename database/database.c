#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define TEMPERATURE_DB      "temperature.db"
#define HUMIDITY_DB         "humidity.db"
#define LIGHT_INTENSITY_DB  "light_inte.db"

#define TEMPERATURE_TABLE       "CREATE TABLE TEMPERATURE(          \
                                    ID INTEDER PRIMARY KEY,         \
                                    LOCATION        VARCHAR(20),    \
                                    TEMP_NUM        INTEGER        \
                                );"

#define HUMIDITY_TABLE          "CREATE TABLE HUMIDITY(             \
                                    ID INTEDER PRIMARY KEY,         \
                                    LOCATION        VARCHAR(20),    \
                                    HUMI_NUM        INTEGER        \
                                );"

#define LIGHT_INTENSITY_TABLE   "CREATE TABLE LIGHT_INTENSITY(      \
                                    ID INTEDER PRIMARY KEY,         \
                                    LOCATION        VARCHAR(20),    \
                                    LIGHNT_INTE     INTEGER        \
                                );"

struct database {
    sqlite3 *sql_db;
    char *sql_table;
    char *insert_data;
    char *get_data;
};

struct database temp_database, humi_database, light_inte_database;

int main(int argc, char *argv[])
{
    int sql_result;
    char *error_msg;

    if((sql_result = sqlite3_open(TEMPERATURE_DB, &temp_database.sql_db)) != SQLITE_OK) {
        printf("temperature: open database fail: %s\n", sqlite3_errmsg(temp_database.sql_db));
        sqlite3_close(temp_database.sql_db);
        exit(1);
    }
    printf("open database success!!!\n");

    if((sql_result = sqlite3_open(HUMIDITY_DB, &humi_database.sql_db)) != SQLITE_OK) {
        printf("humidity: open database fail: %s\n", sqlite3_errmsg(humi_database.sql_db));
        sqlite3_close(humi_database.sql_db);
        exit(1);
    }
    printf("open database success!!!\n");
    
    if((sql_result = sqlite3_open(LIGHT_INTENSITY_DB, &light_inte_database.sql_db)) != SQLITE_OK) {
        printf("light intensity: open database fail: %s\n", sqlite3_errmsg(light_inte_database.sql_db));
        sqlite3_close(light_inte_database.sql_db);
        exit(1);
    }
    printf("open database success!!!\n");

    temp_database.sql_table = TEMPERATURE_TABLE;
    //humi_database.sql_table = HUMIDITY_TABLE;
    //light_inte_database.sql_table = LIGHT_INTENSITY_TABLE;

    if((sql_result = sqlite3_exec(temp_database.sql_db, temp_database.sql_table, NULL, NULL, &error_msg)) != SQLITE_OK) {
        printf("%s\n",error_msg);
        sqlite3_free(error_msg);
    }

    temp_database.insert_data = "INSERT INTO 'TEMPERATURE'VALUES(NULL, 'bedroom', 28.3);";
    if((sql_result = sqlite3_exec(temp_database.sql_db, temp_database.insert_data, NULL, NULL, &error_msg)) != SQLITE_OK) {
        printf("%s\n",error_msg);
        sqlite3_free(error_msg);
    }
    temp_database.insert_data = "INSERT INTO 'TEMPERATURE'VALUES(NULL, 'bedroom', 30);";
    if((sql_result = sqlite3_exec(temp_database.sql_db, temp_database.insert_data, NULL, NULL, &error_msg)) != SQLITE_OK) {
        printf("%s\n",error_msg);
        sqlite3_free(error_msg);
    }
    return 0;
}
