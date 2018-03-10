// Yuxi Luo (yl4217), February 26, 2018
// CS3113 Game Programming

#include "GameState.h"
#include "../setUp.h"

extern ShaderProgram untextured;
extern ShaderProgram textured;

enum GameMode {STATE_MAIN_MENU, STATE_GAME_LEVEL, STATE_GAME_OVER};
extern GameMode mode;
extern float fixedStep;
extern int maxStep;

GameState::GameState(){
    // default: loading font
    untextured = setUntextured();

    GLuint text;
    textured = setTextured("Asset/font1.png", text);
    disp = Text(&textured, text);

    // inheritance: should take care of loading xml & spritesheet

    // need to implement: initialize the game
    // init();
}


// bullets: disappear when collide
void GameState::checkCollision(){

    // players' bullet: collide with enemy / with board
    for (size_t i = 0; i < player.bul.size(); i++){
        for (size_t j = 0; j < enemygroup.ene.size(); j++){
            if (player.bul[i].collide(enemygroup.ene[j])){
                player.delBullet(i);
                player.incScore(10);
                enemygroup.delEne(j);
            }
        }
    }

    // enemy's bullet: collide with player / with board
    for (size_t i = 0; i < enemygroup.ene.size(); i++){
        for (size_t j = 0; j < enemygroup.ene[i].bul.size(); j++){
            if (enemygroup.ene[i].bul[j].collide(player)){
                player.decLives();
                enemygroup.ene[i].delBullet(j);
            }
        }
    }
}

void GameState::update(float elapsed){
    switch (mode){
        case STATE_MAIN_MENU:
            break;
        case STATE_GAME_LEVEL:
            checkCollision();
            player.update(elapsed);
            enemygroup.update(elapsed);
            if (player.getLives() == 0 || enemygroup.getEne() == 0) mode = STATE_GAME_OVER;
            break;
        case STATE_GAME_OVER:
            break;
    }
}

void GameState::fixedUpdate(float lastFrameTicks, float accumulator){
    // update parameters
    float ticks = (float)SDL_GetTicks()/1000.0f;
    float elapsed = ticks - lastFrameTicks;
    lastFrameTicks = ticks;

    // get elapsed time
    elapsed += accumulator;
    if (elapsed < fixedStep) {
        accumulator = elapsed;
        return;
    }

    int count = 0;
    while (elapsed >= fixedStep) {
        update(fixedStep);
        elapsed -= fixedStep;
        count += 1;

        if (count >= maxStep) break;
    }
    accumulator = elapsed;
}


void GameState::render(){
    switch (mode){
        case STATE_MAIN_MENU:
            displayMainMenu();
            break;
        case STATE_GAME_LEVEL:
            displayLevel();
            break;
        case STATE_GAME_OVER:
            displayOver();
            break;
    }

}


void GameState::displayMainMenu(){}

void GameState::displayLevel(){}

void GameState::displayOver(){}
