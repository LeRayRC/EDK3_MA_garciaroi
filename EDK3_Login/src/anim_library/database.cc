#include "database.h"

#include <stdio.h>
#include <string>

#include "animationinstance.h"
#include "game.h"

Database::Database() {}

Database::~Database() {
  close();
}

int Database::connect(const char *path) {

  result_code = sqlite3_open(path, &database);
  if (result_code != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(database));
    sqlite3_close(database);
    return 1;
  } else {
    fprintf(stdout, "Database opened\n");
    return 0;
  }
}

int Database::close() {
  sqlite3_free(err_msg);
  return sqlite3_close(database);
}

int Database::runQuery(const char *query, int (*callback)(void *, int, char **, char **), void *variable) {
  result_code = sqlite3_exec(database, query, callback, variable, &err_msg);

  if (result_code != SQLITE_OK) {
    return 1;
  } else {
    return SQLITE_OK;
  }
}

int Database::processSettings(void *not_used, int num_columns, char **col_values, char **col_names) {

  // not_used=0;
  if (!strcmp(col_values[1], "SCREEN_WINDOW_HEIGHT")) {
    // // g_settings.screen_window_height
    // sscanf(argv[2],"%d",&g_settings.screen_window_height);
    // if(g_settings.screen_window_height < 256 ||
    //     g_settings.screen_window_height > 4096) {
    //     g_settings.screen_window_height = 1024;
  }
  // }else if(!strcmp(argv[1], "SCREEN_WINDOW_WIDTH")) {
  //     sscanf(argv[2], "%d",&g_settings.screen_window_width);
  // }else if(!strcmp(argv[1], "FPS_FPS")){
  //     sscanf(argv[2], "%c", &g_settings.fps_fps);
  // }else if(!strcmp(argv[1], "PLAYER_MOUSE_OFFSET")){
  //     sscanf(argv[2], "%f", &g_settings.player_mouse_offset);
  // }else if(!strcmp(argv[1], "BALL_COUNT")){
  //     sscanf(argv[2], "%d", &g_settings.ball_count);
  // }else if(!strcmp(argv[1], "BALL_REBOUND_SPEED")){
  //     sscanf(argv[2], "%d", &g_settings.ball_rebound_speed);
  // }else if(!strcmp(argv[1], "BRICK_ROWS")){
  //     sscanf(argv[2], "%d", &g_settings.brick_rows);
  // }else if(!strcmp(argv[1], "BRICK_COLUMNS")){
  //     sscanf(argv[2], "%d", &g_settings.brick_columns);
  // }else if(!strcmp(argv[1], "BRICK_OFFSET")){
  //     sscanf(argv[2], "%f", &g_settings.brick_offset);
  // }else if(!strcmp(argv[1], "POWERUP_TOTAL")){
  //     sscanf(argv[2], "%d", &g_settings.powerup_total);
  else {
    // printf("Undefined setting %s with value %s\n", argv[1], argv[2]);
  }
  return 0;
}

int Database::processAnimations(void *not_used, int num_columns, char **col_values, char **col_names) {
  AnimationConfig temp_config;
  int temp_value;
  if (!strcmp(col_names[0], "id_animation")) {
    sscanf(col_values[0], "%d", &temp_config.id);
  }
  if (!strcmp(col_names[1], "name")) {
    // snprintf(&temp_config.name[0],strlen(col_values[1]),"%s",col_values[1]);
    temp_config.name = col_values[1];
    // sscanf(col_values[1], "%s", temp_config.name.c_str);
  }
  if (!strcmp(col_names[2], "is_moving")) {
    sscanf(col_values[2], "%d", &temp_value);
    temp_config.is_moving = (temp_value != 0);
  }
  if (!strcmp(col_names[3], "is_rotating")) {
    sscanf(col_values[3], "%d", &temp_value);
    temp_config.is_rotating = (temp_value != 0);
  }
  if (!strcmp(col_names[4], "is_scaling")) {
    sscanf(col_values[4], "%d", &temp_value);
    temp_config.is_scaling = (temp_value != 0);
  }
  if (!strcmp(col_names[5], "move_from_X")) {
    sscanf(col_values[5], "%f", &temp_config.move_from.x);
  }
  if (!strcmp(col_names[6], "move_from_Y")) {
    sscanf(col_values[6], "%f", &temp_config.move_from.y);
  }
  if (!strcmp(col_names[7], "move_to_X")) {
    sscanf(col_values[7], "%f", &temp_config.move_to.x);
  }
  if (!strcmp(col_names[8], "move_to_Y")) {
    sscanf(col_values[8], "%f", &temp_config.move_to.y);
  }
  if (!strcmp(col_names[9], "move_duration")) {
    sscanf(col_values[9], "%f", &temp_config.move_duration);
  }
  if (!strcmp(col_names[10], "rotate_from")) {
    sscanf(col_values[10], "%f", &temp_config.rotate_from);
  }
  if (!strcmp(col_names[11], "rotate_to")) {
    sscanf(col_values[11], "%f", &temp_config.rotate_to);
  }
  if (!strcmp(col_names[12], "rotate_duration")) {
    sscanf(col_values[12], "%f", &temp_config.rotate_duration);
  }
  if (!strcmp(col_names[13], "scale_from_X")) {
    sscanf(col_values[13], "%f", &temp_config.scale_from.x);
  }
  if (!strcmp(col_names[14], "scale_from_Y")) {
    sscanf(col_values[14], "%f", &temp_config.scale_from.y);
  }
  if (!strcmp(col_names[15], "scale_to_X")) {
    sscanf(col_values[15], "%f", &temp_config.scale_to.x);
  }
  if (!strcmp(col_names[16], "scale_to_Y")) {
    sscanf(col_values[16], "%f", &temp_config.scale_to.y);
  }
  if (!strcmp(col_names[17], "scale_duration")) {
    sscanf(col_values[17], "%f", &temp_config.scale_duration);
  }
  if (!strcmp(col_names[18], "interpolation")){
    int temp_type;
    sscanf(col_values[18], "%d", &temp_type);
    temp_config.type_ = static_cast<InterpolationType>(temp_type);
  }
  

  Game::getInstance()->animation_configs_.push_back(temp_config);
  Game::getInstance()->animation_configs_db_.push_back(temp_config);

  return 0;
}

void Database::insertAnimation(AnimationConfig animation) {
  char query[4096];
  snprintf(query, 4096, "INSERT INTO animations (name, \
                                                is_moving,\
                                                is_rotating,\
                                                is_scaling,\
                                                move_from_X,\
                                                move_from_Y,\
                                                move_to_X,\
                                                move_to_Y,\
                                                move_duration,\
                                                rotate_from,\
                                                rotate_to,\
                                                rotate_duration,\
                                                scale_from_X,\
                                                scale_from_Y,\
                                                scale_to_X, \
                                                scale_to_Y, \
                                                scale_duration, \
                                                interpolation) \
  VALUES ('%s', %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d)",
           animation.name.c_str(),
           animation.is_moving,
           animation.is_rotating,
           animation.is_scaling,
           animation.move_from.x,
           animation.move_from.y,
           animation.move_to.x,
           animation.move_to.y,
           animation.move_duration,
           animation.rotate_from,
           animation.rotate_to,
           animation.rotate_duration,
           animation.scale_from.x,
           animation.scale_from.y,
           animation.scale_to.x,
           animation.scale_to.y,
           animation.scale_duration,
           static_cast<int>(animation.type_));

  // printf("%s\n", query);
  runQuery(query, nullptr, 0);
}

void Database::saveAnimation(AnimationConfig animation, AnimationConfig reference) {
  // Determine if the animation is on the DB or not

  char query[4096] = {'\0'};
  // char temp_string[1024];

  snprintf(query, 4096, "UPDATE animations SET  name = '%s',\
                                                is_moving = %d,\
                                                is_rotating = %d,\
                                                is_scaling = %d,\
                                                move_from_X = %f,\
                                                move_from_Y = %f,\
                                                move_to_X = %f,\
                                                move_to_Y = %f,\
                                                move_duration = %f,\
                                                rotate_from = %f,\
                                                rotate_to = %f,\
                                                rotate_duration = %f,\
                                                scale_from_X = %f,\
                                                scale_from_Y = %f,\
                                                scale_to_X = %f,\
                                                scale_to_Y = %f,\
                                                scale_duration  = %f,\
                                                interpolation = %d\
                                          WHERE name = '%s' and \
                                                is_moving = %d and \
                                                is_rotating = %d and \
                                                is_scaling = %d and \
                                                move_from_X = %f and \
                                                move_from_Y = %f and \
                                                move_to_X = %f and \
                                                move_to_Y = %f and \
                                                move_duration = %f and \
                                                rotate_from = %f and \
                                                rotate_to = %f and \
                                                rotate_duration = %f and \
                                                scale_from_X = %f and \
                                                scale_from_Y = %f and \
                                                scale_to_X = %f and \
                                                scale_to_Y = %f and \
                                                scale_duration  = %f and \
                                                interpolation = %d",
           animation.name.c_str(),
           animation.is_moving,
           animation.is_rotating,
           animation.is_scaling,
           animation.move_from.x,
           animation.move_from.y,
           animation.move_to.x,
           animation.move_to.y,
           animation.move_duration,
           animation.rotate_from,
           animation.rotate_to,
           animation.rotate_duration,
           animation.scale_from.x,
           animation.scale_from.y,
           animation.scale_to.x,
           animation.scale_to.y,
           animation.scale_duration,
           static_cast<int>(animation.type_),

           reference.name.c_str(),
           reference.is_moving,
           reference.is_rotating,
           reference.is_scaling,
           reference.move_from.x,
           reference.move_from.y,
           reference.move_to.x,
           reference.move_to.y,
           reference.move_duration,
           reference.rotate_from,
           reference.rotate_to,
           reference.rotate_duration,
           reference.scale_from.x,
           reference.scale_from.y,
           reference.scale_to.x,
           reference.scale_to.y,
           reference.scale_duration,
           static_cast<int>(reference.type_));

  // printf("%s ",query);
  if (runQuery(query, nullptr, 0) != SQLITE_OK) {
    // printf("%s\n", Game::getInstance()->db_.err_msg);
  }
}

bool Database::deleteAnimation(AnimationConfig *animation, AnimationConfig *reference) {
  // Determine if the animation is on the DB or not

  char query[4096] = {'\0'};
  // char temp_string[1024];

  snprintf(query, 4096, "DELETE FROM animations \
                          WHERE name = '%s' and \
                                is_moving = %d and \
                                is_rotating = %d and \
                                is_scaling = %d and \
                                move_from_X = %f and \
                                move_from_Y = %f and \
                                move_to_X = %f and \
                                move_to_Y = %f and \
                                move_duration = %f and \
                                rotate_from = %f and \
                                rotate_to = %f and \
                                rotate_duration = %f and \
                                scale_from_X = %f and \
                                scale_from_Y = %f and \
                                scale_to_X = %f and \
                                scale_to_Y = %f and \
                                scale_duration  = %f and \
                                interpolation = %d",

           reference->name.c_str(),
           reference->is_moving,
           reference->is_rotating,
           reference->is_scaling,
           reference->move_from.x,
           reference->move_from.y,
           reference->move_to.x,
           reference->move_to.y,
           reference->move_duration,
           reference->rotate_from,
           reference->rotate_to,
           reference->rotate_duration,
           reference->scale_from.x,
           reference->scale_from.y,
           reference->scale_to.x,
           reference->scale_to.y,
           reference->scale_duration,
           static_cast<int>(reference->type_));

  // printf("%s ",query);
  if (runQuery(query, nullptr, 0) == SQLITE_OK) {
    Game *game = Game::getInstance(); 
    
    for(int i=0;i< game->animation_configs_.size();i++){
      if(&game->animation_configs_[i] == animation){
        game->animation_configs_.erase(game->animation_configs_.begin()+i);
      }
    }
    for (int i = 0; i < game->animation_configs_db_.size(); i++) {
      if (&game->animation_configs_db_[i] == reference) {
        game->animation_configs_db_.erase(game->animation_configs_db_.begin() + i);
      }
    }
    return true;
  }
  else
  {
    printf("%s\n", Game::getInstance()->db_.err_msg);
    return false;
  }
}