#include "documentstab.h"

DocumentStab::DocumentStab(QObject* parent) : QObject(parent) {}

void DocumentStab::update() { emit updateHTML(); }
