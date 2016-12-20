/**
 * @file console.h
 * @date 2016-12-20
 * @author flomll (mueller@mllapps.com)
 *
 * Copyright (C) <year>  <name of author>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @brief Console widget interface
 */
#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>


class Console : public QPlainTextEdit
{

signals:
public:
    Console(QWidget * parent = 0);

    void mousePressEvent(QMouseEvent * e);
};

#endif // CONSOLE_H
