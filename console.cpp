/**
 * @file console.cpp
 * @date 2016-12-20
 * @author flomll (mueller@mllapps.com)
 *
 * Copyright (C) 2016  www.mllapps.com
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
 * @brief Console widget implementation
 */
#include <QDebug>
#include <QTextCursor>
#include <QApplication>
#include <QClipboard>

#include "console.h"

Console::Console(QWidget * parent) : QPlainTextEdit(parent)
{

}

void Console::mousePressEvent(QMouseEvent *e)
{
    QClipboard * cb = QApplication::clipboard();
    cb->clear(QClipboard::Clipboard);

    QTextCursor c = this->textCursor();
    c.setPosition(0, QTextCursor::MoveAnchor);
    c.setPosition(this->toPlainText().count(), QTextCursor::KeepAnchor);
    this->setTextCursor(c);

    cb->setText(this->toPlainText(), QClipboard::Clipboard);
}
