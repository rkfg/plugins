/*
 * controller.cpp - plugin
 * Copyright (C) 2011  Khryukin Evgeny
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

#include "controller.h"

#include "screenshot.h"
#include "server.h"
#include "options.h"
#include "screenshoticonset.h"
#include "defines.h"
#include "applicationinfoaccessinghost.h"

static const QString pixacadem = "Pix.Academ.info&split&http://pix.academ.info/&split&&split&&split&action=upload_image&split&image&split&<div id='link'><a id=\"original\" href=\"(http[^\"]+)\"&split&true";
static const QString smages = "Smages.com&split&http://smages.com/&split&&split&&split&&split&fileup&split&<div class=\"codex\"><a href=\"(http://smages.com/[^\"]+)\" target=\"_blank\">URL:</a></div>&split&true";

static const QStringList staticHostsList = QStringList() /*<< imageShack*/ << pixacadem << smages;


static bool isListContainsServer(const QString& server, const QStringList& servers)
{
	foreach(QString serv, servers) {
		if(serv.split(Server::splitString()).first() == server.split(Server::splitString()).first())
			return true;
	}
	return false;
}

static void updateServer(QStringList *const servers, const QString& serv)
{
	QStringList::iterator it = servers->begin();
	while(++it != servers->end()) {
		const QStringList tmpOld = (*it).split(Server::splitString());
		const QStringList tmpNew = serv.split(Server::splitString());
		if(tmpOld.first() == tmpNew.first()) {
			*it = serv;
		}
	}
}


Controller::Controller(ApplicationInfoAccessingHost* appInfo)
	: QObject()
	, appInfo_(appInfo)
{
	Options* o = Options::instance();
	QVariant vServers = o->getOption(constServerList);

	if(!vServers.isValid()) { //приложение запущено впервые
		o->setOption(constShortCut, QVariant("Alt+Shift+p"));
		o->setOption(constFormat, QVariant("png"));
		o->setOption(constFileName, QVariant("pic-yyyyMMdd-hhmmss"));
		o->setOption(constDelay, QVariant(0));
		o->setOption(constVersionOption, cVersion);
		o->setOption(constDefaultAction, QVariant(Desktop));
	}

	QStringList servers = vServers.toStringList();
	foreach(const QString& host, staticHostsList) {
		if(!isListContainsServer(host, servers))
			servers.append(host);
	}

	if(o->getOption(constVersionOption).toString() != cVersion) {
//		foreach(const QString& host, staticHostsList) {
//			updateServer(&servers, host);
//		}
		//updateServer(&servers, ompldr);

		doUpdate();
		o->setOption(constVersionOption, cVersion);
	}

	o->setOption(constServerList, servers); //сохраняем обновленный список серверов
}

Controller::~Controller()
{
	if (screenshot) {
		delete screenshot;
	}

	Options::reset();
	ScreenshotIconset::reset();
}


void Controller::onShortCutActivated()
{
	if(!screenshot) {
		screenshot = new Screenshot();
		screenshot->setProxy(appInfo_->getProxyFor(constName));
	}

	screenshot->action(Options::instance()->getOption(constDefaultAction).toInt());
}

void Controller::openImage()
{
	if(!screenshot) {
		screenshot = new Screenshot();
		screenshot->setProxy(appInfo_->getProxyFor(constName));
	}

	screenshot->openImage();
}

void Controller::doUpdate()
{
	// do some updates
}
