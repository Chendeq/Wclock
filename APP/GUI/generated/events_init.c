/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "lcd.h"
#include "app.h"
#include "wifi.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void wifi_screen_wifi_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.wifi_screen_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void wifi_screen_connect_btn_event_handler (lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        const char *ssid = lv_textarea_get_text(ui->wifi_screen_ssid_textarea);
        const char *password = lv_textarea_get_text(ui->wifi_screen_pwd_textarea);
        (void)wifi_request_connect(ssid, password);
        app_update_wifi_screen_ui(ui);
        break;
    }
    default:
        break;
    }
}

static void wifi_screen_pwd_show_imgbtn_event_handler (lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        uint8_t show_password = lv_obj_has_state(ui->wifi_screen_pwd_show_imgbtn, LV_STATE_CHECKED) ? 1U : 0U;
        lv_textarea_set_password_mode(ui->wifi_screen_pwd_textarea, show_password ? false : true);
        break;
    }
    default:
        break;
    }
}

void events_init_wifi_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->wifi_screen_wifi_back_btn, wifi_screen_wifi_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->wifi_screen_connect_btn, wifi_screen_connect_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->wifi_screen_pwd_show_imgbtn, wifi_screen_pwd_show_imgbtn_event_handler, LV_EVENT_ALL, ui);
}

static void main_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.main_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

/*
* @brief 当点击背光亮度设置按钮时同步显示main_screen_light_set_cont容器上控件内容
*/
static void main_screen_light_sync(lv_ui *ui, uint8_t percent)
{
    char text[8];

    lv_snprintf(text, sizeof(text), "%u%%", percent);
    lv_label_set_text(ui->main_screen_light_value_label, text);
    lv_slider_set_value(ui->main_screen_light_slider, percent, LV_ANIM_OFF);
}

static void main_screen_light_btn_event_handler (lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        main_screen_light_sync(ui, app_get_brightness_percent());
        lv_obj_clear_flag(guider_ui.main_screen_light_set_cont, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void main_screen_light_slider_event_handler (lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        uint8_t value = (uint8_t)lv_slider_get_value(ui->main_screen_light_slider);
        char text[8];

        lv_snprintf(text, sizeof(text), "%u%%", value);
        lv_label_set_text(ui->main_screen_light_value_label, text);
        app_set_manual_brightness(value);
        break;
    }
    default:
        break;
    }
}

static void main_screen_cancel_imgbtn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.main_screen_light_set_cont, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void main_screen_auto_light_sw_event_handler (lv_event_t *e)
{
    lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        app_set_auto_brightness((uint8_t)status);
        if (!status)
        {
            main_screen_light_sync(ui, app_get_brightness_percent());
        }
        break;
    }
    default:
        break;
    }
}

void events_init_main_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->main_screen, main_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_light_btn, main_screen_light_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_light_slider, main_screen_light_slider_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_cancel_imgbtn, main_screen_cancel_imgbtn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_auto_light_sw, main_screen_auto_light_sw_event_handler, LV_EVENT_ALL, ui);        
}

static void setting_screen_setting_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.setting_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void setting_screen_setting_list_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.wifi_screen, guider_ui.wifi_screen_del, &guider_ui.setting_screen_del, setup_scr_wifi_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void setting_screen_setting_list_item2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.alarm_screen, guider_ui.alarm_screen_del, &guider_ui.setting_screen_del, setup_scr_alarm_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_setting_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->setting_screen_setting_back_btn, setting_screen_setting_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->setting_screen_setting_list_item0, setting_screen_setting_list_item0_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->setting_screen_setting_list_item2, setting_screen_setting_list_item2_event_handler, LV_EVENT_ALL, ui);
}

static void software_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.software_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void software_screen_setting_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.software_screen_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void software_screen_weather_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.weather_screen, guider_ui.weather_screen_del, &guider_ui.software_screen_del, setup_scr_weather_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void software_screen_calendar_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.calendar_screen, guider_ui.calendar_screen_del, &guider_ui.software_screen_del, setup_scr_calendar_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void software_screen_calculate_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.calculate_screen, guider_ui.calculate_screen_del, &guider_ui.software_screen_del, setup_scr_calculate_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void software_screen_peripheral_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.peripheral_screen, guider_ui.peripheral_screen_del, &guider_ui.software_screen_del, setup_scr_peripheral_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void software_screen_file_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_software_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->software_screen, software_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_setting_btn, software_screen_setting_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_weather_btn, software_screen_weather_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_calendar_btn, software_screen_calendar_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_calculate_btn, software_screen_calculate_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_peripheral_btn, software_screen_peripheral_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->software_screen_file_btn, software_screen_file_btn_event_handler, LV_EVENT_ALL, ui);
}

static void calendar_screen_calendar_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.calendar_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_calendar_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->calendar_screen_calendar_back_btn, calendar_screen_calendar_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void calculate_screen_calculate_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.calculate_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void calculate_screen_calculate_btnm_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        break;
    }
    default:
        break;
    }
}

void events_init_calculate_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->calculate_screen_calculate_back_btn, calculate_screen_calculate_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->calculate_screen_calculate_btnm, calculate_screen_calculate_btnm_event_handler, LV_EVENT_ALL, ui);
}

static void peripheral_screen_peripheral_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.peripheral_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_peripheral_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->peripheral_screen_peripheral_back_btn, peripheral_screen_peripheral_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void weather_screen_weather_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.software_screen, guider_ui.software_screen_del, &guider_ui.weather_screen_del, setup_scr_software_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_weather_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->weather_screen_weather_back_btn, weather_screen_weather_back_btn_event_handler, LV_EVENT_ALL, ui);
}

static void alarm_screen_alarm_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.setting_screen, guider_ui.setting_screen_del, &guider_ui.alarm_screen_del, setup_scr_setting_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void alarm_screen_alarm_set_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.alarm_set_screen, guider_ui.alarm_set_screen_del, &guider_ui.alarm_screen_del, setup_scr_alarm_set_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void alarm_screen_alarm_set_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.alarm_set_screen, guider_ui.alarm_set_screen_del, &guider_ui.alarm_screen_del, setup_scr_alarm_set_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void alarm_screen_alarm_sw_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        break;
    }
    default:
        break;
    }
}

static void alarm_screen_alarm_sw_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;
        break;
    }
    default:
        break;
    }
}

void events_init_alarm_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->alarm_screen_alarm_back_btn, alarm_screen_alarm_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->alarm_screen_alarm_set_btn_1, alarm_screen_alarm_set_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->alarm_screen_alarm_set_btn_2, alarm_screen_alarm_set_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->alarm_screen_alarm_sw_1, alarm_screen_alarm_sw_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->alarm_screen_alarm_sw_2, alarm_screen_alarm_sw_2_event_handler, LV_EVENT_ALL, ui);
}

static void alarm_set_screen_alarm_set_back_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.alarm_screen, guider_ui.alarm_screen_del, &guider_ui.alarm_set_screen_del, setup_scr_alarm_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void alarm_set_screen_confirm_btn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_alarm_set_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->alarm_set_screen_alarm_set_back_btn, alarm_set_screen_alarm_set_back_btn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->alarm_set_screen_confirm_btn, alarm_set_screen_confirm_btn_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
