/**
 * @file database.h
 * @author Luis Miguel Jiménez
 * @brief header file for the database class to store and acces animations and project settings
 */
#ifndef DATABASE_H_
#define DATABASE_H_ 1

#include "animationinstance.h"

#include <stdlib.h>
#include <string>

#ifdef _ESAT_BACKEND
    #include "esat_extra/sqlite3.h"
#else
    #include "sqlite3.h"
#endif

/**
 * @brief Class that represents a SQLite Database Connection and its functionalities
 * 
 */
class Database{
  //Attributes
  private:
    sqlite3* database;
    int result_code;
  public:
    char* err_msg;

  //Methods
  public:
    // Constructor
    Database();
    // Destructor
    ~Database();

  /**
   * @brief Connects to a SQLite database.
   *
   * This function attempts to open a connection to a SQLite database located at the
   * specified path. If the connection is successful, it prints a message to the standard
   * output indicating that the database has been opened. If the connection fails, an error
   * message is printed to the standard error output, and the function returns an error code.
   *
   * @param path A pointer to the path of the SQLite database file.
   * @return 0 if the connection is successful, 1 if there is an error opening the database.
   */
  int connect(const char* path);

  /**
   * @brief Closes the connection to the SQLite database.
   *
   * This function closes the connection to the SQLite database previously opened with
   * the connect function. It also frees any memory allocated for error messages during
   * the database operations.
   *
   * @return SQLITE_OK if the connection is successfully closed, an error code otherwise.
   */
  int close();

  /**
   * @brief Executes an SQL query on the SQLite database.
   *
   * This function executes the provided SQL query on the connected SQLite database.
   * The query result is processed by the specified callback function, and additional
   * user-specific data can be passed through the 'variable' parameter. If the query
   * execution is successful, the function returns SQLITE_OK; otherwise, it returns an
   * error code.
   *
   * @param query A pointer to the SQL query to be executed.
   * @param callback A callback function to process the query result.
   * @param variable A pointer to user-specific data to be passed to the callback function.
   * @return SQLITE_OK if the query is successfully executed, an error code otherwise.
   */
  int runQuery(const char * query, int (*callback)(void *, int, char **, char **), void *variable);
    
    
  static int processSettings(void *not_used, int argc, char** argv, char** azcolname);
 
  /**
   * @brief Callback function to process animation data retrieved from the database.
   *
   * This function serves as a callback for processing animation data retrieved from
   * an SQLite database. It populates an AnimationConfig structure with values from the
   * database columns and adds the configured animation to the list of animation
   * configurations in the Game instance.
   *
   * @param not_used A pointer to unused data (not used in this function).
   * @param num_columns The number of columns in the result set.
   * @param col_values An array of strings representing the values in each column.
   * @param col_names An array of strings representing the names of the columns.
   * @return Always returns 0 to indicate successful processing.
   */
  static int processAnimations(void *not_used, int argc, char **argv, char **azcolname);

  /**
   * @brief Updates an existing animation configuration in the SQLite database.
   *
   * This function generates and executes an SQL query to update an existing animation
   * configuration in the 'animations' table of the SQLite database. The provided
   * AnimationConfig structure is used to populate the values for each column in the update query.
   *
   * @param animation The AnimationConfig structure containing the updated animation configuration.
   */
  void saveAnimation(AnimationConfig animation, AnimationConfig reference);

  /**
   * @brief Inserts an animation configuration into the SQLite database.
   *
   * This function generates and executes an SQL query to insert a new animation configuration
   * into the SQLite database. The provided AnimationConfig structure is used to populate the
   * values for each column in the 'animations' table.
   *
   * @param animation The AnimationConfig structure containing the animation configuration to be inserted.
   */
  void insertAnimation(AnimationConfig animation);

  /**
   * @brief Deletes an animation from the database and removes it from the internal lists.
   *
   * This function deletes an animation from the database based on the provided reference
   * animation's attributes. It also removes the animation and its reference from the internal
   * lists of animations in the Game instance.
   *
   * @param animation Pointer to the AnimationConfig instance to be deleted.
   * @param reference Pointer to the reference AnimationConfig instance used for deletion criteria.
   *
   * @return Returns true if the deletion is successful, false otherwise.
   *
   * @note The function compares animation instances using memory address.
   *       If the reference animation is found and successfully deleted from the database,
   *       the corresponding animation instances are removed from the internal lists.
   */
  bool deleteAnimation(AnimationConfig *animation, AnimationConfig *reference);
};

#endif