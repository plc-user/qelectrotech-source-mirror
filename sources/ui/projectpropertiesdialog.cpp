/*
	Copyright 2006-2025 The QElectroTech Team
	This file is part of QElectroTech.

	QElectroTech is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	QElectroTech is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with QElectroTech.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "projectpropertiesdialog.h"

#include "../configdialog.h"
#include "configpage/configpages.h"
#include "configpage/projectconfigpages.h"
#include "../TerminalStrip/ui/ConfigPage/terminalstripprojectconfigpage.h"

#include <QObject>

/**
	@brief ProjectPropertiesDialog::ProjectPropertiesDialog
	Default constructor
	@param project : project to edit properties
	@param parent : parent widget of this dialog
*/
ProjectPropertiesDialog::ProjectPropertiesDialog(QETProject *project, QWidget *parent)
{
	m_properties_dialog = new ConfigDialog (parent);
	m_properties_dialog -> setWindowTitle(QObject::tr("Propriétés du projet", "window title"));
	m_properties_dialog -> addPage(new ProjectMainConfigPage(project));

	NewDiagramPage *newDiagramPage = new NewDiagramPage(project,parent,this);
	m_properties_dialog -> addPage(newDiagramPage);

	ProjectAutoNumConfigPage *projectAutoNumConfigPage = new ProjectAutoNumConfigPage (project);
	m_properties_dialog -> addPage(projectAutoNumConfigPage);

	m_properties_dialog->addPage(new TerminalStripProjectConfigPage { project, parent });

	connect(projectAutoNumConfigPage,SIGNAL(setAutoNum(QString)),newDiagramPage,SLOT(setFolioAutonum(QString)));
	connect(projectAutoNumConfigPage,SIGNAL(saveCurrentTbp()),newDiagramPage,SLOT(saveCurrentTbp()));
	connect(projectAutoNumConfigPage,SIGNAL(loadSavedTbp()),newDiagramPage,SLOT(loadSavedTbp()));
}

/**
	@brief ProjectPropertiesDialog::~ProjectPropertiesDialog
*/
ProjectPropertiesDialog::~ProjectPropertiesDialog ()
{
	delete m_properties_dialog;
}

/**
	@brief ProjectPropertiesDialog::exec
	execute this dialog.
*/
void ProjectPropertiesDialog::exec()
{
	m_properties_dialog->setWindowModality(Qt::WindowModal);
	m_properties_dialog -> exec();
}

/**
	@brief ProjectPropertiesDialog::setCurrentPage
	Change the current displayed page by p.
	@param p : page to display
*/
void ProjectPropertiesDialog::setCurrentPage(ProjectPropertiesDialog::Page p) {
	m_properties_dialog -> setCurrentPage(static_cast <int> (p));
}

/**
	@brief ProjectPropertiesDialog::changeToFolio
	Change the current displayed tab to folio tab.
*/
void ProjectPropertiesDialog::changeToFolio()
{
	ProjectAutoNumConfigPage *autoNumPage =
			static_cast <ProjectAutoNumConfigPage*>(
				m_properties_dialog->pages.at(2));
	autoNumPage->changeToTab(3);
}
