#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "clock.h"
#include "colors.h"

Clock::Clock()
        : m_radius(0.42), m_line_width(0.035) {
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &Clock::on_timeout), 1000);
}

Clock::~Clock() {
}

bool Clock::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    cr->scale(width, height);
    cr->translate(0.5, 0.5);

    cr->set_line_width(m_line_width);

    cr->save();
    cr->set_source_rgba(WIDGET_BG_COLOR);
    cr->paint();
    cr->restore();
    cr->set_source_rgba(CLOCK_BORDER_COLOR);
    cr->arc(0, 0, m_radius, 0, 2 * M_PI);
    cr->save();
    cr->set_source_rgba(CLOCK_BG_COLOR);
    cr->fill_preserve();
    cr->restore();
//  cr->stroke_preserve();
    cr->clip();

    cr->arc(0, 0, m_radius - 0.015, 0, 2 * M_PI);
    cr->clip();

    //clock ticks
    for (int i = 0; i < 60; i++) {
        double inset = 0.09;
//        double outset = 0.03;

        cr->set_source_rgba(CLOCK_TICKS_COLOR);
        cr->save();
        cr->set_line_cap(LINE_CAP_TICKS);

        if (i % 5 != 0) {
            inset = 0.053;
//            outset = 0.02;
            cr->set_line_width(0.008);
        }

        cr->move_to(
                (m_radius - inset) * cos(i * M_PI / 30),
                (m_radius - inset) * sin(i * M_PI / 30));
        cr->line_to(
                (m_radius) * cos(i * M_PI / 30),
                (m_radius) * sin(i * M_PI / 30));
        cr->stroke();
        cr->restore(); /* stack-pen-size */
    }

    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds = timeinfo->tm_sec * M_PI / 30;

    cr->save();
    cr->set_line_cap(LINE_CAP_HANDS);

    // draw the hours hand
    cr->set_source_rgba(HOUR_HAND_COLOR);   // green
    cr->move_to(sin(hours + minutes / 12.0) * -(m_radius * 0.25),
                -cos(hours + minutes / 12.0) * -(m_radius * 0.25));
    cr->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
                -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    cr->stroke();
    cr->restore();

    // draw the minutes hand
    cr->set_source_rgba(MIN_HAND_COLOR);   // blue
    cr->move_to(sin(minutes + seconds / 60) * -(m_radius * 0.25),
                -cos(minutes + seconds / 60) * -(m_radius * 0.25));
    cr->line_to(sin(minutes + seconds / 60) * (m_radius * 0.85),
                -cos(minutes + seconds / 60) * (m_radius * 0.85));
    cr->stroke();


    // draw the seconds hand
    cr->save();
    cr->set_line_width(m_line_width / 4);
    cr->set_source_rgba(SEC_HAND_COLOR); // gray
    cr->move_to(sin(seconds) * -(m_radius * 0.25),
                -cos(seconds) * -(m_radius * 0.25));
    cr->line_to(sin(seconds) * (m_radius * 0.6),
                -cos(seconds) * (m_radius * 0.6));

    cr->stroke();
    cr->restore();


    cr->set_source_rgba(SEC_HAND_COLOR);
    cr->arc(sin(seconds) * (m_radius * 0.6),
            -cos(seconds) * (m_radius * 0.6),
            m_line_width * 0.9, 0, 2 * M_PI);
    cr->fill();

    cr->move_to(0, 0);

    // draw a little dot in the middle
    cr->set_source_rgba(SEC_HAND_COLOR); // gray
    cr->arc(0, 0, m_line_width / 2.5, 0, 2 * M_PI);
    cr->fill();

    // draw a little dot in the middle
    cr->set_source_rgba(MIDDLE_DOT_COLOR);
    cr->arc(0, 0, m_line_width / 8.0, 0, 2 * M_PI);
    cr->fill();

    return true;
}


bool Clock::on_timeout() {
    // force our program to redraw the entire clock.
    auto win = get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}
