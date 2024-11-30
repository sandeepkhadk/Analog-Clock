#include <graphics.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <cstdio> // For sprintf
#define PI 3.1415

void Draw_Clock() {
    circle(250, 250, 200);
    circle(250, 250, 5);

    char label[3];
    for (int i = 1; i <= 12; i++) {
        double angle = i * PI / 6;
        sprintf(label, "%d", i); // Convert integer to string
        outtextxy(245 + 180 * sin(angle), 250 - 180 * cos(angle), label);
    }
}

int main() {
    initwindow(500, 500, "Analog Clock");
    int page = 0;

    while (true) {
        setactivepage(1 - page);
        setvisualpage(page);
        cleardevice();
        Draw_Clock();

        // Get current time
        time_t current = time(0);
        tm* ltm = localtime(&current);

        // Calculate angles for hands
        double hourAngle = (ltm->tm_hour % 12 + ltm->tm_min / 60.0) * PI / 6;
        double minuteAngle = (ltm->tm_min + ltm->tm_sec / 60.0) * PI / 30;
        double secondAngle = ltm->tm_sec * PI / 30;

        // Draw hour hand
        setcolor(RED);
        line(250, 250, 250 + 100 * sin(hourAngle), 250 - 100 * cos(hourAngle));

        // Draw minute hand
        setcolor(GREEN);
        line(250, 250, 250 + 150 * sin(minuteAngle), 250 - 150 * cos(minuteAngle));

        // Draw second hand
        setcolor(WHITE);
        line(250, 250, 250 + 180 * sin(secondAngle), 250 - 180 * cos(secondAngle));

        // Exit condition
        if (GetAsyncKeyState(VK_RETURN)) {
            break;
        }

        delay(1000); // Delay for 1 second
        page = 1 - page;
    }

    closegraph();
    return 0;
}

