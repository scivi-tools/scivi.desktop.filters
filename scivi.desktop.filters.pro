TEMPLATE = subdirs

scivi2core.subdir = scivi.desktop/scivi2core

plugins.subdir = src/lib
plugins.target = plugins
plugins.depends = scivi2core

app.subdir = src/App
app.target = app
app.depends = plugins

SUBDIRS = scivi2core plugins app
