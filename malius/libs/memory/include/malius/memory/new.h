#pragma once

#define MA_NEW(type, arena) new(arena.Allocate(sizeof(type), __FILE__, __LINE__)) type

#define MA_DELETE(type, arena) /*TODO*/
