/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *wifi_screen;
	bool wifi_screen_del;
	lv_obj_t *wifi_screen_cont_1;
	lv_obj_t *wifi_screen_wifi_back_btn;
	lv_obj_t *wifi_screen_wifi_back_btn_label;
	lv_obj_t *wifi_screen_net_config_label;
	lv_obj_t *wifi_screen_wifi_name_label;
	lv_obj_t *wifi_screen_wifi_pwd_label;
	lv_obj_t *wifi_screen_pwd_textarea;
	lv_obj_t *wifi_screen_ssid_textarea;
	lv_obj_t *wifi_screen_connect_btn;
	lv_obj_t *wifi_screen_connect_btn_label;
	lv_obj_t *wifi_screen_pwd_show_imgbtn;
	lv_obj_t *wifi_screen_pwd_show_imgbtn_label;
	lv_obj_t *wifi_screen_connect_status_label;
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_cont_1;
	lv_obj_t *main_screen_time_label;
	lv_obj_t *main_screen_week_label;
	lv_obj_t *main_screen_indoor_cont;
	lv_obj_t *main_screen_indoor_label;
	lv_obj_t *main_screen_temperature_label;
	lv_obj_t *main_screen_air_pressure_label;
	lv_obj_t *main_screen_humidity_label;
	lv_obj_t *main_screen_air_q_label;
	lv_obj_t *main_screen_extern_cont;
	lv_obj_t *main_screen_address_img;
	lv_obj_t *main_screen_address_label;
	lv_obj_t *main_screen_extern_temp_label;
	lv_obj_t *main_screen_wea_status_label;
	lv_obj_t *main_screen_date_label;
	lv_obj_t *main_screen_wifi_img;
	lv_obj_t *main_screen_light_btn;
	lv_obj_t *main_screen_light_btn_label;
	lv_obj_t *main_screen_light_set_cont;
	lv_obj_t *main_screen_light_slider;
	lv_obj_t *main_screen_light_value_label;
	lv_obj_t *main_screen_cancel_imgbtn;
	lv_obj_t *main_screen_cancel_imgbtn_label;
	lv_obj_t *main_screen_auto_light_sw;
	lv_obj_t *main_screen_battery_img;
	lv_obj_t *main_screen_battery_label;
	lv_obj_t *main_screen_ararm_cont;
	lv_obj_t *main_screen_ararm_cancel_imgbtn;
	lv_obj_t *main_screen_ararm_cancel_imgbtn_label;
	lv_obj_t *main_screen_alarm_img;
	lv_obj_t *main_screen_alarm_label;
	lv_obj_t *main_screen_buzzer_label;
	lv_obj_t *main_screen_close_btn;
	lv_obj_t *main_screen_close_btn_label;
	lv_obj_t *setting_screen;
	bool setting_screen_del;
	lv_obj_t *setting_screen_cont_1;
	lv_obj_t *setting_screen_setting_back_btn;
	lv_obj_t *setting_screen_setting_back_btn_label;
	lv_obj_t *setting_screen_setting_title_label;
	lv_obj_t *setting_screen_setting_list;
	lv_obj_t *setting_screen_setting_list_item0;
	lv_obj_t *setting_screen_setting_list_item1;
	lv_obj_t *setting_screen_setting_list_item2;
	lv_obj_t *software_screen;
	bool software_screen_del;
	lv_obj_t *software_screen_cont_1;
	lv_obj_t *software_screen_setting_btn;
	lv_obj_t *software_screen_setting_btn_label;
	lv_obj_t *software_screen_setting_img;
	lv_obj_t *software_screen_weather_img;
	lv_obj_t *software_screen_weather_btn;
	lv_obj_t *software_screen_weather_btn_label;
	lv_obj_t *software_screen_calendar_img;
	lv_obj_t *software_screen_calendar_btn;
	lv_obj_t *software_screen_calendar_btn_label;
	lv_obj_t *software_screen_calculate_img;
	lv_obj_t *software_screen_calculate_btn;
	lv_obj_t *software_screen_calculate_btn_label;
	lv_obj_t *software_screen_peripheral_btn;
	lv_obj_t *software_screen_peripheral_btn_label;
	lv_obj_t *software_screen_peripheral_img;
	lv_obj_t *software_screen_file_img;
	lv_obj_t *software_screen_file_btn;
	lv_obj_t *software_screen_file_btn_label;
	lv_obj_t *calendar_screen;
	bool calendar_screen_del;
	lv_obj_t *calendar_screen_cont_1;
	lv_obj_t *calendar_screen_calendar;
	lv_obj_t *calendar_screen_calendar_back_btn;
	lv_obj_t *calendar_screen_calendar_back_btn_label;
	lv_obj_t *calendar_screen_calendar_title_label;
	lv_obj_t *calculate_screen;
	bool calculate_screen_del;
	lv_obj_t *calculate_screen_cont_1;
	lv_obj_t *calculate_screen_calculate_back_btn;
	lv_obj_t *calculate_screen_calculate_back_btn_label;
	lv_obj_t *calculate_screen_calclulate_title_label;
	lv_obj_t *calculate_screen_calculate_btnm;
	lv_obj_t *calculate_screen_show_label;
	lv_obj_t *peripheral_screen;
	bool peripheral_screen_del;
	lv_obj_t *peripheral_screen_cont_1;
	lv_obj_t *peripheral_screen_spl06_label;
	lv_obj_t *peripheral_screen_lis2dh12tr_label;
	lv_obj_t *peripheral_screen_bh1750_label;
	lv_obj_t *peripheral_screen_sht30_label;
	lv_obj_t *peripheral_screen_peripheral_back_btn;
	lv_obj_t *peripheral_screen_peripheral_back_btn_label;
	lv_obj_t *peripheral_screen_peripheral_title_label;
	lv_obj_t *peripheral_screen_atgm332d_label;
	lv_obj_t *weather_screen;
	bool weather_screen_del;
	lv_obj_t *weather_screen_cont_1;
	lv_obj_t *weather_screen_weather_back_btn;
	lv_obj_t *weather_screen_weather_back_btn_label;
	lv_obj_t *weather_screen_day_label_1;
	lv_obj_t *weather_screen_date_label_1;
	lv_obj_t *weather_screen_wea_label_1;
	lv_obj_t *weather_screen_day_img_1;
	lv_obj_t *weather_screen_daytime_tem_label_1;
	lv_obj_t *weather_screen_day_label_2;
	lv_obj_t *weather_screen_date_label_2;
	lv_obj_t *weather_screen_wea_label_2;
	lv_obj_t *weather_screen_day_img_2;
	lv_obj_t *weather_screen_daytime_tem_label_2;
	lv_obj_t *weather_screen_daytime_tem_label_3;
	lv_obj_t *weather_screen_day_img_3;
	lv_obj_t *weather_screen_wea_label_3;
	lv_obj_t *weather_screen_date_label_3;
	lv_obj_t *weather_screen_day_label_3;
	lv_obj_t *weather_screen_weather_title_label;
	lv_obj_t *alarm_screen;
	bool alarm_screen_del;
	lv_obj_t *alarm_screen_cont_1;
	lv_obj_t *alarm_screen_alarm_back_btn;
	lv_obj_t *alarm_screen_alarm_back_btn_label;
	lv_obj_t *alarm_screen_alarm_set_btn_1;
	lv_obj_t *alarm_screen_alarm_set_btn_1_label;
	lv_obj_t *alarm_screen_alarm_set_btn_2;
	lv_obj_t *alarm_screen_alarm_set_btn_2_label;
	lv_obj_t *alarm_screen_alarm_sw_1;
	lv_obj_t *alarm_screen_alarm_sw_2;
	lv_obj_t *alarm_screen_alarm_label_1;
	lv_obj_t *alarm_screen_alarm_label_2;
	lv_obj_t *alarm_screen_alarm_title_label;
	lv_obj_t *alarm_set_screen;
	bool alarm_set_screen_del;
	lv_obj_t *alarm_set_screen_cont_1;
	lv_obj_t *alarm_set_screen_alarm_set_back_btn;
	lv_obj_t *alarm_set_screen_alarm_set_back_btn_label;
	lv_obj_t *alarm_set_screen_hour_roller;
	lv_obj_t *alarm_set_screen_minute_roller_1;
	lv_obj_t *alarm_set_screen_alarm_set_label;
	lv_obj_t *alarm_set_screen_separation_label;
	lv_obj_t *alarm_set_screen_confirm_btn;
	lv_obj_t *alarm_set_screen_confirm_btn_label;
	lv_obj_t *alarm_set_screen_minute_roller_2;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_wifi_screen(lv_ui *ui);
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_setting_screen(lv_ui *ui);
void setup_scr_software_screen(lv_ui *ui);
void setup_scr_calendar_screen(lv_ui *ui);
void setup_scr_calculate_screen(lv_ui *ui);
void setup_scr_peripheral_screen(lv_ui *ui);
void setup_scr_weather_screen(lv_ui *ui);
void setup_scr_alarm_screen(lv_ui *ui);
void setup_scr_alarm_set_screen(lv_ui *ui);

// LV_FONT_DECLARE(lv_font_Fangzhengcuheisongsimple_14)
// LV_FONT_DECLARE(lv_font_montserratMedium_16)
// LV_FONT_DECLARE(lv_font_Fangzhengcuheisongsimple_16)
// LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
// LV_FONT_DECLARE(lv_font_Fangzhengcuheisongsimple_36)
// LV_FONT_DECLARE(lv_font_Fangzhengcuheisongsimple_18)
// LV_FONT_DECLARE(lv_font_montserratMedium_12)

LV_FONT_DECLARE(lv_Font_7)
LV_FONT_DECLARE(lv_Font_8)
LV_FONT_DECLARE(lv_Font_10)
LV_FONT_DECLARE(lv_Font_12)
LV_FONT_DECLARE(lv_Font_14)


#ifdef __cplusplus
}
#endif
#endif
