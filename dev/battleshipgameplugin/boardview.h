/*
 * boardview.h - Battleship game plugin
 * Copyright (C) 2014  Aleksey Andreev
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QTableView>

#include "boardmodel.h"

class BoardView : public QTableView
{
	Q_OBJECT
public:
	BoardView(QWidget *parent = 0);
	void setModel(BoardModel *model);

private:
	virtual void resizeEvent(QResizeEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	void setCellsSize();

private:
	BoardModel *bmodel_;

};

#endif // BOARDVIEW_H
