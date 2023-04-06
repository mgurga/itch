#pragma once

#define TIME_NOW std::chrono::high_resolution_clock::now()
#define TIMER_START() auto timer_start = TIME_NOW;
#define TIMER_END(x) std::cout << x << " took " << std::chrono::duration_cast<std::chrono::milliseconds>(TIME_NOW - timer_start).count() << " ms" << std::endl;