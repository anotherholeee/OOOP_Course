#ifndef MENU_H
#define MENU_H

#include "worker.h"
#include <string>

void menu();
void save_workers_to_file(Worker* workers[], int count, const std::string& filename);

#endif