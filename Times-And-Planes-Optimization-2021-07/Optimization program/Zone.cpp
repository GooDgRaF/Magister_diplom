//
// Created by Антон on 07.07.2021.
//

#include "Zone.h"
Zone &Zone::get_instance()
        {
        // The only instance of the class is created at the first call get_instance()
        // and will be destroyed only when the program exits
        static Zone instance;
        return instance;
    }
    Zone zone = Zone::get_instance();