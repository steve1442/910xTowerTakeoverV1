#include "main.h"

int auton = 5;
std::string autons[] = {"Red 1", "Red 2", "Blue 1", "Blue 2", "Skills", "None"};
bool exitProgram = false;
enum displayStates {
  DISPLAY_STATE_DEFAULT = 0,
  DISPLAY_STATE_AUTON = 1,
  DISPLAY_STATE_STATS = 2,
  DISPLAY_STATE_EXIT = 3
};

bool isAuton;

int displayState = DISPLAY_STATE_DEFAULT;
int currentOpacity = 100;
bool opaIncreasing = true;

//functions
void selectAuton() {
  const char * autonOptions[] = {"<Red Flags>", "<Red Caps>", "<Blue Flags>", "<Blue Caps>", "<Skills>", "<Disable>"};
  int selection = 0;
  while(auton == -1) {
    controller.clear();
    controller.print(0, 0, "Select auton:");
    controller.print(1, 0, autonOptions[selection]);
    controller.print(2, 2, "A to select");
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      auton = selection;
      while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
        pros::delay(1);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
      selection = (selection - 1 >= 0) ? selection - 1 : 5;
      while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))
        pros::delay(1);
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      selection = (selection + 1 < 6) ? selection + 1 : 0;
      while(controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT))
        pros::delay(1);
    }
    pros::delay(50);
  }
  controller.clear();
}

void defaultScreen() {
  while(displayState == DISPLAY_STATE_DEFAULT)
    pros::delay(1);
}

static lv_res_t resolveAutonSelection(lv_obj_t * btn, const char * txt) {
  if(!strcmp(txt, "Red 1"))
    auton = 0;
  else if(!strcmp(txt, "Red 2"))
    auton = 1;
  else if(!strcmp(txt, "Blue 1"))
    auton = 2;
  else if(!strcmp(txt, "Blue 2"))
    auton = 3;
  else if(!strcmp(txt, "Skills"))
    auton = 4;
  else
    auton = 5;
  displayState = DISPLAY_STATE_DEFAULT;
  return LV_RES_OK;
}

static lv_res_t resolveAutonPress(lv_obj_t * btn) {
  displayState = DISPLAY_STATE_AUTON;
  return LV_RES_OK;
}

static lv_res_t resolveExitPress(lv_obj_t * btn) {
  displayState = DISPLAY_STATE_EXIT;
  return LV_RES_OK;
}

void autonSelectionScreen() {
  while(displayState == DISPLAY_STATE_AUTON)
    pros::delay(1);
}

void updateAutonText(lv_obj_t * label) {
  std::string selectedAuton = autons[auton];
  std::string text = "Auton:\n" + selectedAuton;
  lv_label_set_text(label, text.c_str());
}

void run() {
  //STYLES

  static lv_style_t backgroundStyle;
  lv_style_copy(&backgroundStyle, &lv_style_pretty_color);
  backgroundStyle.body.main_color = LV_COLOR_WHITE;
  backgroundStyle.body.grad_color = LV_COLOR_BLUE;
  backgroundStyle.body.radius = 0;
  backgroundStyle.body.border.color = LV_COLOR_BLACK;
  backgroundStyle.body.border.width = 5;

  static lv_style_t buttonStyle;
  lv_style_copy(&buttonStyle, &lv_style_pretty_color);
  buttonStyle.body.main_color = LV_COLOR_WHITE;
  buttonStyle.body.grad_color = LV_COLOR_WHITE;
  buttonStyle.body.opa = 100;
  buttonStyle.body.border.color = LV_COLOR_BLACK;
  buttonStyle.body.border.width = 2;
  buttonStyle.body.border.opa = 255;
  buttonStyle.text.color = LV_COLOR_BLACK;

  static lv_style_t buttonStylePressed;
  lv_style_copy(&buttonStylePressed, &buttonStyle);
  buttonStylePressed.body.opa = 50;
  buttonStylePressed.text.color = LV_COLOR_WHITE;

  static lv_style_t buttonStyle_bg;
  lv_style_copy(&buttonStyle_bg, &lv_style_pretty_color);
  buttonStyle_bg.body.main_color = LV_COLOR_BLACK;
  buttonStyle_bg.body.grad_color = LV_COLOR_BLACK;
  buttonStyle_bg.body.opa = 100;
  buttonStyle_bg.body.border.color = LV_COLOR_BLACK;
  buttonStyle_bg.body.border.width = 2;
  buttonStyle_bg.body.radius = 0;
  buttonStyle_bg.body.border.opa = 255;
  buttonStyle_bg.body.padding.ver = 25;
  buttonStyle_bg.body.padding.hor = 25;
  buttonStyle_bg.body.padding.inner = 25;
  buttonStyle_bg.text.color = LV_COLOR_BLACK;

  static lv_style_t logoTextStyle;
  lv_style_copy(&logoTextStyle, &lv_style_plain);
  extern lv_font_t lv_font_dejavu_20;
  logoTextStyle.text.font = &lv_font_dejavu_20;

  static _lv_obj_t * background = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_style(background, &backgroundStyle);
  lv_obj_set_size(background, 480, 240);
  lv_obj_set_pos(background, 0, 0);

  //OBJECTS
  static _lv_obj_t * imageBackground = lv_obj_create(background, NULL);
  lv_obj_set_style(imageBackground, &buttonStyle);
  lv_obj_set_size(imageBackground, 315, 220);
  lv_obj_set_pos(imageBackground, 10, 10);


  LV_IMG_DECLARE(AutonSelect910);
  lv_obj_t * imgAutonSelect910 = lv_img_create(background, NULL);
  lv_obj_align(imgAutonSelect910, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);
  lv_img_set_src(imgAutonSelect910, &AutonSelect910);

  static _lv_obj_t * autonButton = lv_btn_create(background, NULL);
  lv_btn_set_style(autonButton, LV_BTN_STYLE_PR, &buttonStylePressed);
  lv_btn_set_style(autonButton, LV_BTN_STYLE_REL, &buttonStyle);
  lv_obj_set_size(autonButton, 140, 50);
  lv_obj_set_pos(autonButton, 330, 10);
  lv_btn_set_action(autonButton, LV_BTN_ACTION_CLICK, resolveAutonPress);

  static _lv_obj_t * autonLabel = lv_label_create(autonButton, NULL);
  lv_obj_align(autonLabel, NULL, LV_ALIGN_CENTER, 0, 0);

  static _lv_obj_t * exitButton = lv_btn_create(background, NULL);
  lv_btn_set_style(exitButton, LV_BTN_STYLE_PR, &buttonStylePressed);
  lv_btn_set_style(exitButton, LV_BTN_STYLE_REL, &buttonStyle);
  lv_obj_set_size(exitButton, 60, 50);
  lv_obj_set_pos(exitButton, 370, 180);
  lv_btn_set_action(exitButton, LV_BTN_ACTION_CLICK, resolveExitPress);

  static _lv_obj_t * exitLabel = lv_label_create(exitButton, NULL);
  lv_label_set_text(exitLabel, "Exit");
  lv_obj_align(exitLabel, NULL, LV_ALIGN_CENTER, 0, 0);

  static const char * map[] = {"Red 1", "Red 2", "Skills", "\n", "Blue 1", "Blue 2", "None", ""};
  lv_obj_t * buttons = lv_btnm_create(background, NULL);
  lv_btnm_set_map(buttons, map);
  lv_btnm_set_style(buttons, LV_BTNM_STYLE_BG, &buttonStyle_bg);
  lv_btnm_set_style(buttons, LV_BTNM_STYLE_BTN_PR, &buttonStylePressed);
  lv_btnm_set_style(buttons, LV_BTNM_STYLE_BTN_REL, &buttonStyle);
  lv_obj_set_size(buttons, 480, 240);
  lv_btnm_set_action(buttons, resolveAutonSelection);

  lv_obj_t * defaultScreenObjects[] = {imageBackground, autonButton, exitButton, imgAutonSelect910};
  lv_obj_t * autonScreenObjects[] = {buttons};

  while(!exitProgram) {
    if(displayState == DISPLAY_STATE_DEFAULT) {
      for(lv_obj_t * x : autonScreenObjects)
        lv_obj_set_hidden(x, true);
      for(lv_obj_t * x : defaultScreenObjects)
        lv_obj_set_hidden(x, false);
      updateAutonText(autonLabel);
      //lv_obj_set_hidden(imageBackground, true);
      //lv_obj_set_hidden(autonButton, true);
      //lv_obj_set_hidden(exitButton, true);
      while(displayState == DISPLAY_STATE_DEFAULT) {
        if(opaIncreasing) {
          backgroundStyle.body.opa = currentOpacity++;
          if(currentOpacity == 255) {
            pros::delay(1000);
            opaIncreasing = false;
          }
        }
        else {
          backgroundStyle.body.opa = currentOpacity--;
          if(currentOpacity == 100) {
            pros::delay(1000);
            opaIncreasing = true;
          }
        }
        lv_obj_set_style(background, &backgroundStyle);
        pros::delay(20);
      }
    }
    else if(displayState == DISPLAY_STATE_AUTON) {
      for(lv_obj_t * x : autonScreenObjects)
        lv_obj_set_hidden(x, false);
      for(lv_obj_t * x : defaultScreenObjects)
        lv_obj_set_hidden(x, true);
      while(displayState == DISPLAY_STATE_AUTON) {
        if(opaIncreasing) {
          backgroundStyle.body.opa = currentOpacity++;
          if(currentOpacity == 255) {
            pros::delay(1000);
            opaIncreasing = false;
          }

        }
        else {
          backgroundStyle.body.opa = currentOpacity--;
          if(currentOpacity == 100) {
            pros::delay(1000);
            opaIncreasing = true;
          }
        }
        lv_obj_set_style(background, &backgroundStyle);
        pros::delay(20);
      }
    }
    else if(displayState == DISPLAY_STATE_STATS) {

    }
    else if(displayState == DISPLAY_STATE_EXIT) {
      exitProgram = true;
    }
    else {

    }
    pros::delay(20);
  }
  lv_obj_del(background);
}
bool skylineImage = true;
void coolDisplay(_lv_obj_t * background,lv_style_t backgroundStyle){

  if(opaIncreasing) {
          backgroundStyle.body.opa = currentOpacity++;
          if(currentOpacity == 255) {
            pros::delay(1000);
            opaIncreasing = false;
          }
        }
        else {
          backgroundStyle.body.opa = currentOpacity--;
          if(currentOpacity == 100) {
            pros::delay(1000);
            opaIncreasing = true;
          }
        }
        lv_obj_set_style(background, &backgroundStyle);
        pros::delay(20);
}
bool runOnce = false;
static lv_res_t skylinePic(lv_obj_t * btn){

  skylineImage = !skylineImage;
  return LV_RES_OK;
}

static lv_res_t debugg(lv_obj_t * btn){

  return LV_RES_OK;
}

void debugScreenInit(){

}
static _lv_obj_t * background = lv_obj_create(lv_scr_act(), NULL);
static lv_style_t backgroundStyle;
static lv_style_t buttonInvis;
static lv_style_t buttonStyle;
static lv_style_t buttonStylePressed;
static lv_style_t buttonStyle_bg;
static lv_style_t logoTextStyle;


//static _lv_obj_t * exitButto = lv_btn_create(lv_scr_act(), NULL);
lv_obj_t * imgskyline = lv_img_create(lv_scr_act(), NULL);
static _lv_obj_t * exitButton = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_t * imgdebug910 = lv_img_create(background, NULL);
lv_obj_t * bar2 = lv_bar_create(background, NULL);
static _lv_obj_t * tabview = lv_tabview_create(background, NULL);
lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Main");
lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Drive");
lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Lift");
lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "Intake");
lv_obj_t * labe = lv_label_create(tab2, NULL);
void debugScreen(){

  //STYLES


	lv_obj_align(imgskyline, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_img_set_src(imgskyline, &skylinelogo);

  lv_style_copy(&backgroundStyle, &lv_style_pretty_color);
  backgroundStyle.body.main_color = LV_COLOR_WHITE;
  backgroundStyle.body.grad_color = LV_COLOR_BLUE;
  backgroundStyle.body.radius = 0;
  backgroundStyle.body.border.color = LV_COLOR_BLACK;
  backgroundStyle.body.border.width = 5;


  lv_style_copy(&buttonInvis, &lv_style_pretty_color);
  buttonInvis.body.main_color = LV_COLOR_WHITE;
  buttonInvis.body.grad_color = LV_COLOR_WHITE;
  buttonInvis.body.opa = 0;
  buttonInvis.body.border.color = LV_COLOR_BLACK;
  buttonInvis.body.border.width = 0;
  buttonInvis.body.border.opa = 0;
  buttonInvis.text.color = LV_COLOR_BLACK;



  lv_style_copy(&buttonStyle, &lv_style_pretty_color);
  buttonStyle.body.main_color = LV_COLOR_WHITE;
  buttonStyle.body.grad_color = LV_COLOR_WHITE;
  buttonStyle.body.opa = 100;
  buttonStyle.body.border.color = LV_COLOR_BLACK;
  buttonStyle.body.border.width = 2;
  buttonStyle.body.border.opa = 255;
  buttonStyle.text.color = LV_COLOR_BLACK;


  lv_style_copy(&buttonStylePressed, &buttonStyle);
  buttonStylePressed.body.opa = 50;
  buttonStylePressed.text.color = LV_COLOR_WHITE;


  lv_style_copy(&buttonStyle_bg, &lv_style_pretty_color);
  buttonStyle_bg.body.main_color = LV_COLOR_BLACK;
  buttonStyle_bg.body.grad_color = LV_COLOR_BLACK;
  buttonStyle_bg.body.opa = 0;
  buttonStyle_bg.body.border.color = LV_COLOR_BLACK;
  buttonStyle_bg.body.border.width = 2;
  buttonStyle_bg.body.radius = 0;
  buttonStyle_bg.body.border.opa = 0;
  buttonStyle_bg.body.padding.ver = 25;
  buttonStyle_bg.body.padding.hor = 25;
  buttonStyle_bg.body.padding.inner = 25;
  buttonStyle_bg.text.color = LV_COLOR_BLACK;


  lv_style_copy(&logoTextStyle, &lv_style_plain);
  extern lv_font_t lv_font_dejavu_20;
  logoTextStyle.text.font = &lv_font_dejavu_20;

  lv_obj_set_style(background, &backgroundStyle);
  lv_obj_set_size(background, 480, 240);
  lv_obj_set_pos(background, 0, 0);

  //OBJECTS


	lv_obj_align(imgdebug910, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_img_set_src(imgdebug910, &debuglogo);


  lv_btn_set_style(exitButton, LV_BTN_STYLE_PR, &buttonInvis);
  lv_btn_set_style(exitButton, LV_BTN_STYLE_REL, &buttonInvis);
  lv_obj_set_size(exitButton, 200, 200);
  lv_obj_set_pos(exitButton, 0, 0);
  lv_btn_set_action(exitButton, LV_BTN_ACTION_CLICK, skylinePic);

/*
  lv_btn_set_style(exitButto, LV_BTN_STYLE_PR, &buttonInvis);
  lv_btn_set_style(exitButto, LV_BTN_STYLE_REL, &buttonInvis);
  lv_obj_set_size(exitButto, 480, 240);
  lv_obj_set_pos(exitButto, 0, 0);
  lv_btn_set_action(exitButto, LV_BTN_ACTION_CLICK, skylinePic);
*/

  //LV_IMG_DECLARE(imgdebug910);


lv_obj_align(tabview, NULL, LV_ALIGN_IN_TOP_LEFT, 200, 0);
lv_obj_set_size(tabview, 280, 240);
lv_obj_set_style(tabview, &backgroundStyle);
/*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/


/*Add content to the tabs*/
lv_obj_t * label = lv_label_create(tab1, NULL);
lv_label_set_text(label, "This the first tab\n\n"
                         "If the content\n"
                         "become too long\n"
                         "the tab become\n"
                         "scrollable\n\n");






lv_obj_t * labell = lv_label_create(tab3, NULL);
lv_label_set_text(labell, "Third tab");

lv_obj_t * labelll = lv_label_create(tab4, NULL);
lv_label_set_text(labelll, "4th tab");


/*
lv_obj_t * bar1 = lv_bar_create(lv_scr_act(), NULL);
lv_obj_set_size(bar1, 200, 30);
lv_obj_align(bar1, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 30);
lv_bar_set_value(bar1, 70);


lv_obj_t * bar1_label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_text(bar1_label, "Default");
lv_obj_align(bar1_label, bar1, LV_ALIGN_OUT_LEFT_MID, -10, 0);
*/

static lv_style_t style_bar;
static lv_style_t style_indic;

lv_style_copy(&style_bar, &lv_style_pretty);
style_bar.body.main_color = LV_COLOR_BLACK;
style_bar.body.grad_color = LV_COLOR_GRAY;
style_bar.body.radius = LV_RADIUS_CIRCLE;
style_bar.body.border.color = LV_COLOR_WHITE;

lv_style_copy(&style_indic, &lv_style_pretty);
style_indic.body.grad_color =  LV_COLOR_GREEN;
style_indic.body.main_color=  LV_COLOR_LIME;
style_indic.body.radius = LV_RADIUS_CIRCLE;
style_indic.body.shadow.width = 10;
style_indic.body.shadow.color = LV_COLOR_LIME;
style_indic.body.padding.hor = 3;
style_indic.body.padding.ver = 3;


lv_bar_set_style(bar2, LV_BAR_STYLE_BG, &style_bar);
lv_bar_set_style(bar2, LV_BAR_STYLE_INDIC, &style_indic);
lv_obj_set_size(bar2, 200, 30);
lv_obj_align(bar2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 190);

}





void continuous(){
  //coolDisplay(background, backgroundStyle);
      //read sensor val


     //sensor val converted to string
     //set text of the label to x
    int gyroVal = 5;//gyro.get_value();
  std::string temp = "gyro val " + std::to_string(gyroVal);
  const char * x = temp.c_str();
  lv_label_set_text(labe, x);
  lv_bar_set_value(bar2, pros::c::battery_get_capacity());
  if(skylineImage){
      lv_obj_set_hidden(background, true);
      lv_obj_set_hidden(imgskyline, false);
      lv_obj_set_size(exitButton, 480, 240);
  }
  else{
      lv_obj_set_hidden(background, false);
      lv_obj_set_hidden(imgskyline, true);
      lv_obj_set_size(exitButton, 200, 200);
  }
}

void notContinuous(){

}
