#pragma once

enum viewtype {TOP_VIEW, PERSPECTIVE_VIEW, RAT_VIEW};
extern viewtype CURRENT_VIEW;

void DrawLine(double x1, double y1, double x2, double y2);
void DrawCircle(double x1, double y1, double radius, double deviation);
void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawText(double x, double y, const char *string);
