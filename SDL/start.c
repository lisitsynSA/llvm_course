extern void simInit();
extern void app();
extern void simExit();

int main(void)
{
    simInit();
    app();
    simExit();
    return 0;
}