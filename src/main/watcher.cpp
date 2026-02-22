#include "Web.hpp"
#include "Backup.hpp"
int main()
{
    // Backup<Web> web("web");
    // cin >> web->input();
    // web->calculate();
    // cout << web->output();
    Backup<Web> web("Lans");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Matrix tmp(20, 1);
            tmp(i) = tmp(10 + j) = 1;
            web->input() = tmp;
            web->calculate();
            int mx = web->output()(0), ans = 0;
            for (int k = 1; k < 10; k++)
                if (mx < web->output()(k))
                {
                    mx = web->output()(k);
                    ans = k;
                }
            cout << i << "+" << j << "=" << ans;
            if (ans == (i + j) % 10)
                cout << " AC\n";
            else
                cout << " WA\n";
        }
    }
    return 0;
}