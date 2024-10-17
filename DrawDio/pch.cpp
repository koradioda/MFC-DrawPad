// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。
CPoint SLayer::m_ptDrag{ MAXWORD,MAXWORD }, SLayer::m_pt2{ m_ptDrag }, SLayer::m_ptLast{ m_ptDrag };//光标不可能到达的位置，0,-1，-8等等是有可能到达的。