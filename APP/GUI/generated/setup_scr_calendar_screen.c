/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



lv_calendar_date_t calendar_screen_calendar_today;
lv_calendar_date_t calendar_screen_calendar_highlihted_days[1];
void setup_scr_calendar_screen(lv_ui *ui)
{
    //Write codes calendar_screen
    ui->calendar_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->calendar_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->calendar_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for calendar_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calendar_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calendar_screen_cont_1
    ui->calendar_screen_cont_1 = lv_obj_create(ui->calendar_screen);
    lv_obj_set_pos(ui->calendar_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->calendar_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->calendar_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for calendar_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calendar_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->calendar_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->calendar_screen_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->calendar_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calendar_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calendar_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calendar_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calendar_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calendar_screen_calendar
    ui->calendar_screen_calendar = lv_calendar_create(ui->calendar_screen_cont_1);
    calendar_screen_calendar_today.year = 2026;
    calendar_screen_calendar_today.month = 7;
    calendar_screen_calendar_today.day = 7;
    lv_calendar_set_today_date(ui->calendar_screen_calendar, calendar_screen_calendar_today.year, calendar_screen_calendar_today.month, calendar_screen_calendar_today.day);
    lv_calendar_set_showed_date(ui->calendar_screen_calendar, calendar_screen_calendar_today.year, calendar_screen_calendar_today.month);
    calendar_screen_calendar_highlihted_days[0].year = 2026;
    calendar_screen_calendar_highlihted_days[0].month = 7;
    calendar_screen_calendar_highlihted_days[0].day = 8;
    lv_calendar_set_highlighted_dates(ui->calendar_screen_calendar, calendar_screen_calendar_highlihted_days, 1);
    lv_obj_t *calendar_screen_calendar_header = lv_calendar_header_arrow_create(ui->calendar_screen_calendar);
    lv_calendar_t *calendar_screen_calendar = (lv_calendar_t *)ui->calendar_screen_calendar;
    lv_obj_add_event_cb(calendar_screen_calendar->btnm, calendar_screen_calendar_draw_part_begin_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(ui->calendar_screen_calendar, calendar_screen_calendar_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->calendar_screen_calendar, 0, 20);
    lv_obj_set_size(ui->calendar_screen_calendar, 320, 190);

    //Write style state: LV_STATE_DEFAULT for &style_calendar_screen_calendar_main_main_default
    static lv_style_t style_calendar_screen_calendar_main_main_default;
    ui_init_style(&style_calendar_screen_calendar_main_main_default);

    lv_style_set_border_width(&style_calendar_screen_calendar_main_main_default, 1);
    lv_style_set_border_opa(&style_calendar_screen_calendar_main_main_default, 255);
    lv_style_set_border_color(&style_calendar_screen_calendar_main_main_default, lv_color_hex(0xc0c0c0));
    lv_style_set_border_side(&style_calendar_screen_calendar_main_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_bg_opa(&style_calendar_screen_calendar_main_main_default, 255);
    lv_style_set_bg_color(&style_calendar_screen_calendar_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_calendar_screen_calendar_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_shadow_width(&style_calendar_screen_calendar_main_main_default, 0);
    lv_style_set_radius(&style_calendar_screen_calendar_main_main_default, 0);
    lv_obj_add_style(ui->calendar_screen_calendar, &style_calendar_screen_calendar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_calendar_screen_calendar_extra_header_main_default
    static lv_style_t style_calendar_screen_calendar_extra_header_main_default;
    ui_init_style(&style_calendar_screen_calendar_extra_header_main_default);

    lv_style_set_text_color(&style_calendar_screen_calendar_extra_header_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_calendar_screen_calendar_extra_header_main_default, &lv_font_montserrat_14);
    lv_style_set_text_opa(&style_calendar_screen_calendar_extra_header_main_default, 255);
    lv_style_set_bg_opa(&style_calendar_screen_calendar_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_calendar_screen_calendar_extra_header_main_default, lv_color_hex(0xcacbc6));
    lv_style_set_bg_grad_dir(&style_calendar_screen_calendar_extra_header_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(calendar_screen_calendar_header, &style_calendar_screen_calendar_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_calendar_screen_calendar_main_items_default
    static lv_style_t style_calendar_screen_calendar_main_items_default;
    ui_init_style(&style_calendar_screen_calendar_main_items_default);

    lv_style_set_bg_opa(&style_calendar_screen_calendar_main_items_default, 0);
    lv_style_set_border_width(&style_calendar_screen_calendar_main_items_default, 1);
    lv_style_set_border_opa(&style_calendar_screen_calendar_main_items_default, 255);
    lv_style_set_border_color(&style_calendar_screen_calendar_main_items_default, lv_color_hex(0xc0c0c0));
    lv_style_set_border_side(&style_calendar_screen_calendar_main_items_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_calendar_screen_calendar_main_items_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_calendar_screen_calendar_main_items_default, &lv_font_montserrat_14);
    lv_style_set_text_opa(&style_calendar_screen_calendar_main_items_default, 255);
    lv_obj_add_style(lv_calendar_get_btnmatrix(ui->calendar_screen_calendar), &style_calendar_screen_calendar_main_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes calendar_screen_calendar_back_btn
    ui->calendar_screen_calendar_back_btn = lv_btn_create(ui->calendar_screen_cont_1);
    ui->calendar_screen_calendar_back_btn_label = lv_label_create(ui->calendar_screen_calendar_back_btn);
    lv_label_set_text(ui->calendar_screen_calendar_back_btn_label, "");
    lv_label_set_long_mode(ui->calendar_screen_calendar_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calendar_screen_calendar_back_btn_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->calendar_screen_calendar_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calendar_screen_calendar_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->calendar_screen_calendar_back_btn, 5, 215);
    lv_obj_set_size(ui->calendar_screen_calendar_back_btn, 30, 20);

    //Write style for calendar_screen_calendar_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calendar_screen_calendar_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calendar_screen_calendar_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calendar_screen_calendar_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calendar_screen_calendar_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calendar_screen_calendar_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calendar_screen_calendar_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->calendar_screen_calendar_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->calendar_screen_calendar_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->calendar_screen_calendar_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calendar_screen_calendar_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calendar_screen_calendar_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calendar_screen_calendar_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calendar_screen_calendar_back_btn, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calendar_screen_calendar_title_label
    ui->calendar_screen_calendar_title_label = lv_label_create(ui->calendar_screen_cont_1);
    lv_label_set_text(ui->calendar_screen_calendar_title_label, "日历");
    lv_label_set_long_mode(ui->calendar_screen_calendar_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->calendar_screen_calendar_title_label, 5, 0);
    lv_obj_set_size(ui->calendar_screen_calendar_title_label, 40, 16);

    //Write style for calendar_screen_calendar_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calendar_screen_calendar_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calendar_screen_calendar_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calendar_screen_calendar_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calendar_screen_calendar_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calendar_screen_calendar_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of calendar_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->calendar_screen);

    //Init events for screen.
    events_init_calendar_screen(ui);
}
