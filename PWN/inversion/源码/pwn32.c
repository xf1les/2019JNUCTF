# gcc -m32 -fstack-protector-all -mpreferred-stack-boundary=2 --static -z noexecstack -o pwn
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void Merge(unsigned int a[], int low, int mid, int high, int *cnt);
void Merge_sort(unsigned int a[], int low, int high, int *cnt);
void solve();
void init();
void banner();
void give_task_name();

char name[10];

int main()
{
    init();
    banner();
    give_task_name();
    while (1)
    {
        solve();
        puts("Continue?(y/n)");
        fflush(stdout);
        if (getchar() != 'y')
            break;
        getchar();
    }
    puts("Goodbye~!");

    return 0;
}

void init(){
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
    alarm(5);
}

void banner() {
    puts(".___                                .__");               
    puts("|   | _______  __ ___________  _____|__| ____   ____"); 
    puts("|   |/    \\  \\/ // __ \\_  __ \\/  ___/  |/  _ \\ /    \\"); 
    puts("|   |   |  \\   /\\  ___/|  | \\/\\___ \\|  (  <_> )   |  \\");
    puts("|___|___|  /\\_/  \\___  >__|  /____  >__|\\____/|___|  /");
    puts("         \\/          \\/           \\/               \\/ ");
    fflush(stdout);
}

void give_task_name(){
    puts("Name:");
    read(0, &name, 10);
    printf("Staring task: %s\n", name);
}

void solve()
{

    int cnt = 0;
    unsigned int data[300];
    int i = 0;

    puts("Count?(Input 0 to stop)");
    fflush(stdout);
    scanf("%d", &i);
    getchar();

    for (int j = 0;; j++)
    {
        printf("%d: ", j);
        scanf("%ud", &data[j]);
        if (data[j] == 0)
        {
            getchar();
            break;
        }
    }

    unsigned int *d = (unsigned int *)malloc(i * sizeof(unsigned int));
    memcpy(d, data, i * sizeof(int));

    Merge_sort(d, 0, i - 1, &cnt);
    printf("The result is %d\n", cnt);
    fflush(stdout);

    free(d);
}

void Merge_sort(unsigned int a[], int low, int high, int *cnt)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        Merge_sort(a, low, mid, cnt);
        Merge_sort(a, mid + 1, high, cnt);
        Merge(a, low, mid, high, cnt);
    }
}

void Merge(unsigned int a[], int low, int mid, int high, int *cnt)
{
    int i = low;
    int j = mid + 1;
    int k = 0;

    unsigned int b[high - low + 1];
    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
        {
            b[k++] = a[j++];
            (*cnt) += (mid - i + 1);
        }
    }
    while (i <= mid)
    {
        b[k++] = a[i++];
    }
    while (j <= high)
    {
        b[k++] = a[j++];
    }
    for (k = 0, i = low; i <= high; i++, k++)
    {
        a[i] = b[k];
    }
}
