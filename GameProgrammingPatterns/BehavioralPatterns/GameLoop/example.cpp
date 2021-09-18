double getCurrentTime(){}
void processInput(){}
void   update(){}
void  render(double){}

const double MS_PER_UPDATE = 10;    // 更新步长
int main()
{
    double previous = getCurrentTime();     // 实际当前时间
    double lag = 0.0;       // 游戏当前时间
    // 模拟用户输入，游戏更新以及渲染
    while (true)
    {
        double current = getCurrentTime();
        double elapsed = current - previous;    // 真实耗费的时间
        previous = current;
        lag += elapsed;             

        processInput();

        // 
        while (lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        // 这里除以MS_PER_UPDATE来归一化值。 不管更新的时间步长是多少，
        // 传给render()的值总在0（恰巧在前一帧）到1.0（恰巧在下一帧）之间。 
        // 这样，渲染引擎不必担心帧率。它只需处理0到1的值。
        render(lag / MS_PER_UPDATE);   
    }
}
