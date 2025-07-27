/* 球钟是一个利用球的移动来记录时间的简单装置 它有三个可以容纳若干个球的指示器:分钟指示器，五分钟指示 器，小时指示器 若分钟指示器中有2个球，五分钟指示器中有6个球，小时指示器 中有5个球，则时间为5:32 每过一分钟，球钟就会从球队列的队首取出一个球放入分钟指示器，分钟指示器最多可容纳4个球。当放入第五个球时，在分钟指示器的4个球就会按照他们被放入时的相反顺序加入球队列的队尾。而第五个球就会进入五分钟指示器。按此类推，五分钟指示器最多可放11个球，小时指示器最多可放11个球。 当小时指示器放入第12个球时，原来的11个球按照他们被放入时的相反顺序加入球队列的队尾，然后第12个球也回到队尾，这时，三个指示器均为空，回到初始状态，从而形成一个循环，因此，该球钟表示时间的范围是从0:00到11:59. 现设初始时球队列的球数为27，球钟的三个指示器初态均为空问，要经过多久，球队列才能回复到原来的顺序? */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkqueue.h"
#include "sqstack.h"

// 球钟结构体定义
typedef struct {
    linkqueue* ball_queue;      // 球的队列
    sqstack_t* minute_stack;    // 分钟指示器（最多4个球）
    sqstack_t* fivemin_stack;   // 五分钟指示器（最多11个球）
    sqstack_t* hour_stack;      // 小时指示器（最多11个球）
} ballclock_t;

// 函数声明
ballclock_t* ballclock_create(int ball_count);
void ballclock_destroy(ballclock_t* clock);
void print_queue_content(linkqueue* queue, const char* label);
void print_ballclock_state(ballclock_t* clock);
bool is_queue_original_order(linkqueue* queue, int ball_count);
bool is_ballclock_initial_state(ballclock_t* clock, int ball_count);
void return_balls_to_queue(sqstack_t* stack, linkqueue* queue);
bool ballclock_tick(ballclock_t* clock);
void ballclock_get_time(ballclock_t* clock, int* hours, int* minutes);
long long calculate_reset_time(int ball_count);
void test_ballclock_basic(void);
void test_small_ballclock(void);

// 创建球钟
ballclock_t* ballclock_create(int ball_count) {
    ballclock_t* clock = (ballclock_t*)malloc(sizeof(ballclock_t));
    if (clock == NULL) return NULL;
    
    // 创建队列和栈
    clock->ball_queue = queue_create();
    clock->minute_stack = sqstack_create(4);    // 分钟最多4个球
    clock->fivemin_stack = sqstack_create(11);  // 五分钟最多11个球
    clock->hour_stack = sqstack_create(11);     // 小时最多11个球
    
    // 检查分配是否成功
    if (!clock->ball_queue || !clock->minute_stack || 
        !clock->fivemin_stack || !clock->hour_stack) {
        // 释放已分配的内存
        if (clock->ball_queue) queue_free(clock->ball_queue);
        if (clock->minute_stack) sqstack_destroy(clock->minute_stack);
        if (clock->fivemin_stack) sqstack_destroy(clock->fivemin_stack);
        if (clock->hour_stack) sqstack_destroy(clock->hour_stack);
        free(clock);
        return NULL;
    }
    
    // 初始化球队列，球编号从1到ball_count
    for (int i = 1; i <= ball_count; i++) {
        enqueue(clock->ball_queue, i);
    }
    
    return clock;
}

// 销毁球钟
void ballclock_destroy(ballclock_t* clock) {
    if (clock) {
        if (clock->ball_queue) queue_free(clock->ball_queue);
        if (clock->minute_stack) sqstack_destroy(clock->minute_stack);
        if (clock->fivemin_stack) sqstack_destroy(clock->fivemin_stack);
        if (clock->hour_stack) sqstack_destroy(clock->hour_stack);
        free(clock);
    }
}

// 将栈中的球按逆序放回队列（利用栈的LIFO特性自然实现逆序）
void return_balls_to_queue(sqstack_t* stack, linkqueue* queue) {
    data_t ball;
    while (!sqstack_is_empty(stack)) {
        if (sqstack_pop(stack, &ball) == STACK_SUCCESS) {
            enqueue(queue, ball);
        }
    }
}

// 模拟一分钟的时间流逝
bool ballclock_tick(ballclock_t* clock) {
    if (queue_empty(clock->ball_queue)) {
        return false; // 队列为空，无法继续
    }
    
    // 从队列取出一个球
    datatype ball = dequeue(clock->ball_queue);
    
    // 尝试放入分钟指示器
    if (sqstack_size(clock->minute_stack) < 4) {
        // 分钟指示器未满，直接放入
        sqstack_push(clock->minute_stack, ball);
    } else {
        // 分钟指示器已满（4个球），发生溢出
        // 将4个球按逆序放回队列队尾
        return_balls_to_queue(clock->minute_stack, clock->ball_queue);
        
        // 当前球进入五分钟指示器
        if (sqstack_size(clock->fivemin_stack) < 11) {
            // 五分钟指示器未满，直接放入
            sqstack_push(clock->fivemin_stack, ball);
        } else {
            // 五分钟指示器已满（11个球），发生溢出
            // 将11个球按逆序放回队列队尾
            return_balls_to_queue(clock->fivemin_stack, clock->ball_queue);
            
            // 当前球进入小时指示器
            if (sqstack_size(clock->hour_stack) < 11) {
                // 小时指示器未满，直接放入
                sqstack_push(clock->hour_stack, ball);
            } else {
                // 小时指示器已满（11个球），发生溢出
                // 将11个球按逆序放回队列队尾
                return_balls_to_queue(clock->hour_stack, clock->ball_queue);
                // 当前球也回到队列队尾
                enqueue(clock->ball_queue, ball);
                // 此时所有指示器都为空，时钟回到初始状态
            }
        }
    }
    
    return true;
}

// 获取当前时间显示
void ballclock_get_time(ballclock_t* clock, int* hours, int* minutes) {
    *hours = sqstack_size(clock->hour_stack);
    *minutes = sqstack_size(clock->fivemin_stack) * 5 + sqstack_size(clock->minute_stack);
}

// 检查队列是否恢复到原始状态（1,2,3,...,ball_count）
bool is_queue_original_order(linkqueue* queue, int ball_count) {
    if (queue_empty(queue)) return false;
    
    // 创建临时数组来检查顺序
    int* temp_balls = (int*)malloc(sizeof(int) * ball_count);
    if (temp_balls == NULL) return false;
    
    // 将队列中的球依次取出并记录，同时保存到临时队列以便恢复
    linkqueue* temp_queue = queue_create();
    int count = 0;
    
    // 首先统计队列中的球数
    linkqueue* count_queue = queue_create();
    while (!queue_empty(queue)) {
        datatype ball = dequeue(queue);
        enqueue(count_queue, ball);
        count++;
    }
    
    // 如果球数不等于期望值，直接返回false
    if (count != ball_count) {
        // 恢复队列
        while (!queue_empty(count_queue)) {
            datatype ball = dequeue(count_queue);
            enqueue(queue, ball);
        }
        queue_free(count_queue);
        free(temp_balls);
        return false;
    }
    
    // 记录球的顺序并恢复队列
    count = 0;
    while (!queue_empty(count_queue)) {
        datatype ball = dequeue(count_queue);
        temp_balls[count++] = ball;
        enqueue(queue, ball);
    }
    queue_free(count_queue);
    
    // 检查是否是原始顺序（1, 2, 3, ..., ball_count）
    bool is_original = true;
    for (int i = 0; i < ball_count && is_original; i++) {
        if (temp_balls[i] != i + 1) {
            is_original = false;
        }
    }
    
    free(temp_balls);
    return is_original;
}

// 检查球钟是否回到初始状态
bool is_ballclock_initial_state(ballclock_t* clock, int ball_count) {
    // 检查所有指示器是否为空
    if (!sqstack_is_empty(clock->minute_stack) || 
        !sqstack_is_empty(clock->fivemin_stack) || 
        !sqstack_is_empty(clock->hour_stack)) {
        return false;
    }
    
    // 检查队列是否恢复原始顺序
    return is_queue_original_order(clock->ball_queue, ball_count);
}

// 打印当前球钟状态（调试用）
void print_ballclock_state(ballclock_t* clock) {
    int hours, minutes;
    ballclock_get_time(clock, &hours, &minutes);
    printf("时间: %d:%02d | ", hours, minutes);
    printf("分钟栈: %d个球, 五分钟栈: %d个球, 小时栈: %d个球\n", 
           sqstack_size(clock->minute_stack),
           sqstack_size(clock->fivemin_stack),
           sqstack_size(clock->hour_stack));
}

// 调试函数：打印队列内容
void print_queue_content(linkqueue* queue, const char* label) {
    if (queue_empty(queue)) {
        printf("%s: 队列为空\n", label);
        return;
    }
    
    printf("%s: ", label);
    
    // 临时取出所有球来查看内容
    linkqueue* temp = queue_create();
    int count = 0;
    while (!queue_empty(queue)) {
        datatype ball = dequeue(queue);
        printf("%d ", ball);
        enqueue(temp, ball);
        count++;
        if (count > 50) { // 防止输出过多
            printf("...");
            break;
        }
    }
    
    // 恢复队列
    while (!queue_empty(temp)) {
        datatype ball = dequeue(temp);
        enqueue(queue, ball);
    }
    queue_free(temp);
    
    printf("(共%d个球)\n", count);
}

// 主函数：计算球钟回到原始状态需要的时间
long long calculate_reset_time(int ball_count) {
    ballclock_t* clock = ballclock_create(ball_count);
    if (clock == NULL) {
        printf("创建球钟失败\n");
        return -1;
    }
    
    long long minutes = 0;
    int hours, mins;
    
    printf("开始模拟球钟...\n");
    printf("初始状态: 队列中有%d个球\n", ball_count);
    
    while (true) {
        // 模拟一分钟
        if (!ballclock_tick(clock)) {
            printf("模拟失败：队列为空（经过%lld分钟）\n", minutes);
            printf("可能原因：球数量不足以维持球钟长期运转\n");
            ballclock_destroy(clock);
            return -1;
        }
        
        minutes++;
        
        // 每隔一段时间输出当前状态
        if (ball_count >= 27) {
            // 对于27个或更多球，每12小时输出一次
            if (minutes % 720 == 0) {
                ballclock_get_time(clock, &hours, &mins);
                printf("经过%lld分钟 (%.1f天), 当前时间: %d:%02d\n", 
                       minutes, minutes / 1440.0, hours, mins);
            }
        } else {
            // 对于较少球，更频繁地输出
            if (minutes % 60 == 0) { // 每小时输出一次
                ballclock_get_time(clock, &hours, &mins);
                printf("经过%lld分钟 (%.1f小时), 当前时间: %d:%02d\n", 
                       minutes, minutes / 60.0, hours, mins);
            }
        }
        
        // 检查是否回到初始状态
        if (is_ballclock_initial_state(clock, ball_count)) {
            ballclock_get_time(clock, &hours, &mins);
            printf("\n找到答案！\n");
            printf("球钟回到初始状态需要: %lld 分钟\n", minutes);
            printf("相当于: %.2f 小时\n", minutes / 60.0);
            printf("相当于: %.2f 天\n", minutes / 1440.0);
            printf("最终时间显示: %d:%02d\n", hours, mins);
            break;
        }
        
        // 防止无限循环的安全检查
        long long max_minutes = (ball_count >= 27) ? 100000000LL : 10000LL;
        if (minutes > max_minutes) {
            printf("计算时间过长（超过%lld分钟），可能存在问题\n", max_minutes);
            break;
        }
    }
    
    ballclock_destroy(clock);
    return minutes;
}

// 测试函数：验证球钟基本功能
void test_ballclock_basic() {
    printf("=== 球钟基本功能测试 ===\n");
    
    ballclock_t* clock = ballclock_create(10); // 使用10个球进行测试
    if (clock == NULL) {
        printf("创建球钟失败\n");
        return;
    }
    
    printf("使用10个球进行基本功能测试\n");
    printf("初始状态:\n");
    print_ballclock_state(clock);
    print_queue_content(clock->ball_queue, "队列");
    
    // 模拟前20分钟，重点观察分钟指示器的溢出
    for (int i = 0; i < 20; i++) {
        if (queue_empty(clock->ball_queue)) {
            printf("第%d分钟：队列为空，测试结束\n", i+1);
            break;
        }
        
        ballclock_tick(clock);
        printf("第%2d分钟后: ", i+1);
        print_ballclock_state(clock);
        
        // 在关键时刻显示队列内容
        if (i+1 == 5 || i+1 == 10 || i+1 == 15) {
            print_queue_content(clock->ball_queue, "  队列");
        }
    }
    
    ballclock_destroy(clock);
}

// 测试函数：验证小规模球钟的周期（带调试信息）
void test_small_ballclock() {
    printf("=== 小规模球钟周期测试 ===\n");
    
    // 先测试一个简单的例子来理解球钟行为
    printf("详细测试5个球的球钟前20分钟:\n");
    ballclock_t* clock = ballclock_create(5);
    if (clock != NULL) {
        print_queue_content(clock->ball_queue, "初始队列");
        
        for (int minute = 1; minute <= 20; minute++) {
            if (queue_empty(clock->ball_queue)) {
                printf("第%d分钟: 队列为空，无法继续\n", minute);
                break;
            }
            
            printf("\n--- 第%d分钟 ---\n", minute);
            printf("操作前: ");
            print_ballclock_state(clock);
            print_queue_content(clock->ball_queue, "队列");
            
            ballclock_tick(clock);
            
            printf("操作后: ");
            print_ballclock_state(clock);
            print_queue_content(clock->ball_queue, "队列");
        }
        
        ballclock_destroy(clock);
    }
    
    printf("\n现在测试需要足够球数的情况（15-30个球）:\n");
    for (int balls = 15; balls <= 30; balls += 5) {
        printf("测试%d个球的球钟:\n", balls);
        long long result = calculate_reset_time(balls);
        if (result > 0) {
            printf("%d个球的周期: %lld分钟 (%.2f小时)\n\n", 
                   balls, result, result / 60.0);
        } else {
            printf("%d个球的测试失败\n\n", balls);
        }
    }
}

int main() {
    printf("球钟时间追踪算法\n");
    printf("==================\n\n");
    
    // 基本功能测试
    test_ballclock_basic();
    printf("\n");
    
    // 小规模测试
    test_small_ballclock();
    printf("\n");
    
    // 解决27个球的主要问题
    printf("=== 解决27个球的主要问题 ===\n");
    long long result = calculate_reset_time(27);
    
    if (result > 0) {
        printf("\n最终答案: %lld 分钟\n", result);
        printf("相当于: %.2f 天\n", result / 1440.0);
    } else {
        printf("计算失败\n");
    }
    
    return 0;
}
