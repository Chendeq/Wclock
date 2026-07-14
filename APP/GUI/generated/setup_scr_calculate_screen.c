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



void setup_scr_calculate_screen(lv_ui *ui)
{
    //Write codes calculate_screen
    ui->calculate_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->calculate_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->calculate_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for calculate_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculate_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculate_screen_cont_1
    ui->calculate_screen_cont_1 = lv_obj_create(ui->calculate_screen);
    lv_obj_set_pos(ui->calculate_screen_cont_1, 0, 0);
    lv_obj_set_size(ui->calculate_screen_cont_1, 320, 240);
    lv_obj_set_scrollbar_mode(ui->calculate_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for calculate_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculate_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->calculate_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->calculate_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->calculate_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculate_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculate_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculate_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculate_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculate_screen_calculate_back_btn
    ui->calculate_screen_calculate_back_btn = lv_btn_create(ui->calculate_screen_cont_1);
    ui->calculate_screen_calculate_back_btn_label = lv_label_create(ui->calculate_screen_calculate_back_btn);
    lv_label_set_text(ui->calculate_screen_calculate_back_btn_label, "");
    lv_label_set_long_mode(ui->calculate_screen_calculate_back_btn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->calculate_screen_calculate_back_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->calculate_screen_calculate_back_btn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->calculate_screen_calculate_back_btn_label, LV_PCT(100));
    lv_obj_set_pos(ui->calculate_screen_calculate_back_btn, 5, 215);
    lv_obj_set_size(ui->calculate_screen_calculate_back_btn, 30, 20);

    //Write style for calculate_screen_calculate_back_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->calculate_screen_calculate_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculate_screen_calculate_back_btn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculate_screen_calculate_back_btn, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->calculate_screen_calculate_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_calculate_back_btn, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculate_screen_calculate_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->calculate_screen_calculate_back_btn, "0:/PICTURE/software_icon/back_release_icon.bin", LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->calculate_screen_calculate_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->calculate_screen_calculate_back_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculate_screen_calculate_back_btn, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculate_screen_calculate_back_btn, &lv_Font_7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculate_screen_calculate_back_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculate_screen_calculate_back_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculate_screen_calclulate_title_label
    ui->calculate_screen_calclulate_title_label = lv_label_create(ui->calculate_screen_cont_1);
    lv_label_set_text(ui->calculate_screen_calclulate_title_label, "计算器");
    lv_label_set_long_mode(ui->calculate_screen_calclulate_title_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->calculate_screen_calclulate_title_label, 5, 0);
    lv_obj_set_size(ui->calculate_screen_calclulate_title_label, 60, 15);

    //Write style for calculate_screen_calclulate_title_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculate_screen_calclulate_title_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculate_screen_calclulate_title_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculate_screen_calclulate_title_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculate_screen_calclulate_title_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculate_screen_calclulate_title_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes calculate_screen_calculate_btnm
    ui->calculate_screen_calculate_btnm = lv_btnmatrix_create(ui->calculate_screen_cont_1);
    static const char *calculate_screen_calculate_btnm_text_map[] = {"AC", "del", "%", "÷", "\n", "7", "8", "9", "x", "\n", "4", "5", "6", "-", "\n", "1", "2", "3", "+", "\n", "tab", "0", ".", "=", "",};
    lv_btnmatrix_set_map(ui->calculate_screen_calculate_btnm, calculate_screen_calculate_btnm_text_map);
    lv_obj_set_pos(ui->calculate_screen_calculate_btnm, 0, 52);
    lv_obj_set_size(ui->calculate_screen_calculate_btnm, 310, 160);

    //Write style for calculate_screen_calculate_btnm, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculate_screen_calculate_btnm, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->calculate_screen_calculate_btnm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->calculate_screen_calculate_btnm, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->calculate_screen_calculate_btnm, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculate_screen_calculate_btnm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculate_screen_calculate_btnm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculate_screen_calculate_btnm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculate_screen_calculate_btnm, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->calculate_screen_calculate_btnm, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->calculate_screen_calculate_btnm, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_calculate_btnm, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculate_screen_calculate_btnm, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculate_screen_calculate_btnm, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculate_screen_calculate_btnm, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for calculate_screen_calculate_btnm, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculate_screen_calculate_btnm, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->calculate_screen_calculate_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->calculate_screen_calculate_btnm, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->calculate_screen_calculate_btnm, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculate_screen_calculate_btnm, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculate_screen_calculate_btnm, &lv_Font_10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculate_screen_calculate_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_calculate_btnm, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculate_screen_calculate_btnm, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculate_screen_calculate_btnm, lv_color_hex(0xb2b3b4), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculate_screen_calculate_btnm, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculate_screen_calculate_btnm, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes calculate_screen_show_label
    ui->calculate_screen_show_label = lv_label_create(ui->calculate_screen_cont_1);
    lv_label_set_text(ui->calculate_screen_show_label, "0");
    lv_label_set_long_mode(ui->calculate_screen_show_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->calculate_screen_show_label, 0, 20);
    lv_obj_set_size(ui->calculate_screen_show_label, 310, 30);

    //Write style for calculate_screen_show_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->calculate_screen_show_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->calculate_screen_show_label, &lv_Font_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->calculate_screen_show_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->calculate_screen_show_label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->calculate_screen_show_label, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->calculate_screen_show_label, lv_color_hex(0xa2a2a2), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->calculate_screen_show_label, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->calculate_screen_show_label, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->calculate_screen_show_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->calculate_screen_show_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of calculate_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->calculate_screen);

    //Init events for screen.
    events_init_calculate_screen(ui);
}
