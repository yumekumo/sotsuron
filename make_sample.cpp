#include <iostream>
#include <vector>
#include <random>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

random_device rnd;                         // 非決定的な乱数生成器を生成
mt19937 mt(1919);                          //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
uniform_int_distribution<> rand100(0, 99); // [0, 99] 範囲の一様乱数

struct student
{
    string grade; // s4~6：小学生，c1~3：中学生，k1~3：高校生
    vector<int> subjects;
    int subjects_sum;
    int id;
    vector<vector<int>> schedule;
    vector<int> compatibility;
};

struct teacher
{
    int id;
    vector<int> available_subjects;
    int want_days;
    vector<vector<int>> schedule;
    int work_time_sum;
};

int num_of_students = 130;

int num_of_teachers = 20;

vector<int> memory_id = {9001, 8001, 7001, 6001, 5001, 4001, 3001, 2001, 1001};
//                       s4    s5    s6    c1    c2    c3    k1    k2    k3

void calc_sum_classes(vector<student> sd)
{
    int sum = 0;
    rep(i, num_of_students)
    {
        sum += sd[i].subjects_sum;
    }
    cout << "合計コマ数： " << sum << endl;
}

//ID割り当て
void assaign_id(student &sd)
{
    if (sd.grade == "s4")
    {
        sd.id = memory_id[0];
        memory_id[0]++;
    }
    else if (sd.grade == "s5")
    {
        sd.id = memory_id[1];
        memory_id[1]++;
    }
    else if (sd.grade == "s6")
    {
        sd.id = memory_id[2];
        memory_id[2]++;
    }
    else if (sd.grade == "c1")
    {
        sd.id = memory_id[3];
        memory_id[3]++;
    }
    else if (sd.grade == "c2")
    {
        sd.id = memory_id[4];
        memory_id[4]++;
    }
    else if (sd.grade == "c3")
    {
        sd.id = memory_id[5];
        memory_id[5]++;
    }
    else if (sd.grade == "k1")
    {
        sd.id = memory_id[6];
        memory_id[6]++;
    }
    else if (sd.grade == "k2")
    {
        sd.id = memory_id[7];
        memory_id[7]++;
    }
    else
    {
        sd.id = memory_id[8];
        memory_id[8]++;
    }
}

vector<student> make_student_data()
{
    int tmp;
    vector<student> sd(num_of_students);

    rep(i, num_of_students)
    {
        //学年の決定
        tmp = rand100(mt);
        //0~24:小学生，25~84:中学生，85~99:高校生
        if (tmp < 25)
        {
            //0~4:s4, 5~14:s5, 15~24:s6
            if (tmp < 5)
            {
                sd[i].grade = "s4";
            }
            else if (tmp < 15)
            {
                sd[i].grade = "s5";
            }
            else
            {
                sd[i].grade = "s6";
            }
        }
        else if (tmp < 85)
        {
            //25~39:c1, 40~59:c2, 60~84:c3
            if (tmp < 40)
            {
                sd[i].grade = "c1";
            }
            else if (tmp < 60)
            {
                sd[i].grade = "c2";
            }
            else
            {
                sd[i].grade = "c3";
            }
        }
        else
        {
            //85~94:k1, 95~99:k2
            if (tmp < 95)
            {
                sd[i].grade = "k1";
            }
            else
            {
                sd[i].grade = "k2";
            }
        }
        assaign_id(sd[i]);

        //受講科目数の決定
        vector<int> sub = {0, 0, 0, 0, 0, 0, 0};

        //小学生
        if (sd[i].grade[0] == 's')
        {
            while (true)
            {
                int cnt = 0; //授業コマ数
                //算数
                tmp = rand100(mt);
                if (tmp < 80)
                {
                    sub[0] = 1;
                    cnt++;
                }
                //英語
                tmp = rand100(mt);
                if (tmp < 40)
                {
                    sub[1] = 1;
                    cnt++;
                }
                //国語
                tmp = rand100(mt);
                if (tmp < 50)
                {
                    sub[2] = 1;
                    cnt++;
                }
                //１科目以上受講しているか
                if (cnt > 0)
                {
                    sd[i].subjects = sub;
                    sd[i].subjects_sum = cnt;

                    break;
                }
            }
        }

        //中１
        else if (sd[i].grade == "c1")
        {
            while (true)
            {
                int cnt = 0;
                //数学
                tmp = rand100(mt);
                if (tmp < 80)
                {
                    if (tmp < 10)
                    {
                        sub[0] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[0] = 1;
                        cnt++;
                    }
                }
                //英語
                tmp = rand100(mt);
                if (tmp < 80)
                {
                    if (tmp < 10)
                    {
                        sub[1] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[1] = 1;
                        cnt++;
                    }
                }
                //国語
                tmp = rand100(mt);
                if (tmp < 30)
                {
                    sub[2] = 1;
                    cnt++;
                }
                //理科
                tmp = rand100(mt);
                if (tmp < 10)
                {
                    sub[3] = 1;
                    cnt++;
                }
                //社会
                tmp = rand100(mt);
                if (tmp < 5)
                {
                    sub[4] = 1;
                    cnt++;
                }
                //１科目以上受講しているか
                if (cnt > 0)
                {
                    sd[i].subjects = sub;
                    sd[i].subjects_sum = cnt;
                    break;
                }
            }
        }

        //中2
        else if (sd[i].grade == "c2")
        {
            while (true)
            {
                int cnt = 0;
                //数学
                tmp = rand100(mt);
                if (tmp < 90)
                {
                    if (tmp < 15)
                    {
                        sub[0] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[0] = 1;
                        cnt++;
                    }
                }
                //英語
                tmp = rand100(mt);
                if (tmp < 90)
                {
                    if (tmp < 15)
                    {
                        sub[1] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[1] = 1;
                        cnt++;
                    }
                }
                //国語
                tmp = rand100(mt);
                if (tmp < 40)
                {
                    sub[2] = 1;
                    cnt++;
                }
                //理科
                tmp = rand100(mt);
                if (tmp < 30)
                {
                    sub[3] = 1;
                    cnt++;
                }
                //社会
                tmp = rand100(mt);
                if (tmp < 10)
                {
                    sub[4] = 1;
                    cnt++;
                }
                //１科目以上受講しているか
                if (cnt > 0)
                {
                    sd[i].subjects = sub;
                    sd[i].subjects_sum = cnt;
                    break;
                }
            }
        }

        //中3
        else if (sd[i].grade == "c3")
        {
            while (true)
            {
                int cnt = 0;
                //数学
                tmp = rand100(mt);
                if (tmp < 95)
                {
                    if (tmp < 15)
                    {
                        sub[0] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[0] = 1;
                        cnt++;
                    }
                }
                //英語
                tmp = rand100(mt);
                if (tmp < 95)
                {
                    if (tmp < 15)
                    {
                        sub[1] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[1] = 1;
                        cnt++;
                    }
                }
                //国語
                tmp = rand100(mt);
                if (tmp < 60)
                {
                    sub[2] = 1;
                    cnt++;
                }
                //理科
                tmp = rand100(mt);
                if (tmp < 65)
                {
                    sub[3] = 1;
                    cnt++;
                }
                //社会
                tmp = rand100(mt);
                if (tmp < 30)
                {
                    sub[4] = 1;
                    cnt++;
                }
                //１科目以上受講しているか
                if (cnt > 0)
                {
                    sd[i].subjects = sub;
                    sd[i].subjects_sum = cnt;
                    break;
                }
            }
        }

        //高校生
        else if (sd[i].grade[0] == 'k')
        {
            while (true)
            {
                int cnt = 0;
                //高校数学
                tmp = rand100(mt);
                if (tmp < 70)
                {
                    if (tmp < 20)
                    {
                        sub[5] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[5] = 1;
                        cnt++;
                    }
                }
                //高校英語
                tmp = rand100(mt);
                if (tmp < 70)
                {
                    if (tmp < 10)
                    {
                        sub[6] = 2;
                        cnt += 2;
                    }
                    else
                    {
                        sub[6] = 1;
                        cnt++;
                    }
                }
                //１科目以上受講しているか
                if (cnt > 0)
                {
                    sd[i].subjects = sub;
                    sd[i].subjects_sum = cnt;
                    break;
                }
            }
        }

        //生徒の受講可能スケジュールを作成
        while (true)
        {
            vector<vector<int>> sche(6, vector<int>(4, 0));
            int cnt = 0;
            rep(j, 6)
            {
                //平日
                if (j < 5)
                {
                    tmp = rand100(mt);
                    if (sd[i].grade[0] == 's')
                    {
                        if (tmp < 70)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            cnt += 2;
                        }
                    }
                    else if (sd[i].grade[0] == 'c')
                    {
                        if (tmp < 8)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 4;
                        }
                        else if (tmp < 10)
                        {
                            sche[j][1] = 1;
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 3;
                        }
                        else if (tmp < 60)
                        {
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 2;
                        }
                        else if (tmp < 70)
                        {
                            sche[j][3] = 1;
                            cnt++;
                        }
                    }
                    else
                    {
                        if (tmp < 10)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 3;
                        }
                        else if (tmp < 60)
                        {
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 2;
                        }
                        else if (tmp > 70)
                        {
                            sche[j][3] = 1;
                            cnt++;
                        }
                    }
                }
                //土曜
                else
                {
                    tmp = rand100(mt);
                    if (sd[i].grade[0] == 's')
                    {
                        if (tmp < 25)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            cnt += 2;
                        }
                    }
                    else if (sd[i].grade[0] == 'c')
                    {
                        if (tmp < 5)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            cnt += 2;
                        }
                        else if (tmp < 10)
                        {
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 2;
                        }
                        else if (tmp < 25)
                        {
                            sche[j][1] = 1;
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 3;
                        }
                    }
                    else
                    {
                        if (tmp < 5)
                        {
                            sche[j][0] = 1;
                            sche[j][1] = 1;
                            cnt += 2;
                        }
                        else if (tmp < 10)
                        {
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 2;
                        }
                        else if (tmp < 20)
                        {
                            sche[j][1] = 1;
                            sche[j][2] = 1;
                            sche[j][3] = 1;
                            cnt += 3;
                        }
                    }
                }
            }
            if (cnt > sd[i].subjects_sum)
            {
                sd[i].schedule = sche;
                break;
            }
        }

        //生徒のアンケート結果の作成
        vector<int> c(num_of_teachers, 0);
        rep(i, num_of_teachers)
        {
            tmp = rand100(mt);
            if (tmp < 2)
            {
                c[i] = -2;
            }
            else if (tmp < 5)
            {
                c[i] = -1;
            }
            else if (tmp < 10)
            {
                c[i] = 0;
            }
            else if (tmp < 20)
            {
                c[i] = 1;
            }
            else if (tmp < 30)
            {
                c[i] = 2;
            }
        }
        sd[i].compatibility = c;
    }

    return sd;
}

vector<teacher> make_teacher_data()
{
    vector<teacher> td(num_of_teachers);

    vector<vector<int>> rikei_subject_table = {
        //数　英　 国　 理  社  高数 高英
        {0, 0, 70, 0, 80, 0, 30},     //×
        {0, 20, 20, 20, 10, 30, 30},  //○
        {100, 80, 10, 80, 10, 70, 40} //◎
    };
    vector<vector<int>> bunkei_subject_table = {
        //数　英　 国　 理  社  高数 高英
        {10, 0, 0, 70, 20, 80, 20},   //×
        {30, 10, 10, 20, 30, 10, 30}, //○
        {60, 90, 90, 10, 50, 10, 50}  //◎
    };

    rep(i, num_of_teachers)
    {
        td[i].id = i + 1;

        int tmp;
        //指導可能科目の作成
        tmp = rand100(mt);
        vector<int> avail_sub(7, 0);

        //理系
        if (tmp < 50)
        {
            rep(j, 7)
            {
                //高校英語の例外
                if (j == 6)
                {
                    if (avail_sub[1] < 2)
                    {
                        avail_sub[j] = 0;
                        continue;
                    }
                }
                tmp = rand100(mt);
                if (tmp < rikei_subject_table[0][j])
                {
                    avail_sub[j] = 0;
                }
                else if (tmp < rikei_subject_table[0][j] + rikei_subject_table[1][j])
                {
                    avail_sub[j] = 1;
                }
                else
                {
                    avail_sub[j] = 2;
                }
            }
        }
        //文系
        else
        {
            rep(j, 7)
            {
                //高校数学の例外
                if (j == 5)
                {
                    if (avail_sub[0] < 2)
                    {
                        avail_sub[j] = 0;
                        continue;
                    }
                }
                //高校英語の例外
                if (j == 6)
                {
                    if (avail_sub[1] < 2)
                    {
                        avail_sub[j] = 0;
                        continue;
                    }
                }
                tmp = rand100(mt);
                if (tmp < bunkei_subject_table[0][j])
                {
                    avail_sub[j] = 0;
                }
                else if (tmp < bunkei_subject_table[0][j] + bunkei_subject_table[1][j])
                {
                    avail_sub[j] = 1;
                }
                else
                {
                    avail_sub[j] = 2;
                }
            }
        }

        td[i].available_subjects = avail_sub;

        //出勤日数
        tmp = rand100(mt);
        if (tmp < 5)
            td[i].want_days = 1;
        if (tmp < 40)
            td[i].want_days = 2;
        else if (tmp < 80)
            td[i].want_days = 3;
        else if (tmp < 95)
            td[i].want_days = 4;
        else
            td[i].want_days = 5;

        int cnt = 0;
        int work_time = 0;
        vector<int> week = {0, 0, 0, 0, 0, 0};
        vector<vector<int>> sche(6, vector<int>(4, 0));
        while (cnt < td[i].want_days)
        {
            int tmp_w = rand100(mt) % 6;
            if (week[tmp_w] == 1)
            {
                continue;
            }
            if (tmp_w == 5)
            {
                tmp = rand100(mt);
                if (tmp < 50)
                    continue;
                else
                {
                    tmp = rand100(mt);
                    if (tmp < 60)
                    {
                        sche[tmp_w][0] = 1;
                        sche[tmp_w][1] = 1;
                        sche[tmp_w][2] = 1;
                        sche[tmp_w][3] = 1;
                        work_time += 4;
                    }
                    else if (tmp < 65)
                    {
                        sche[tmp_w][1] = 1;
                        sche[tmp_w][2] = 1;
                        sche[tmp_w][3] = 1;
                        work_time += 3;
                    }
                    else
                    {
                        sche[tmp_w][2] = 1;
                        sche[tmp_w][3] = 1;
                        work_time += 2;
                    }
                    cnt++;
                    week[tmp_w] = 1;
                    continue;
                }
            }
            if (week[tmp_w] == 0)
            {
                tmp = rand100(mt);
                if (tmp < 50)
                {
                    sche[tmp_w][0] = 1;
                    sche[tmp_w][1] = 1;
                    sche[tmp_w][2] = 1;
                    sche[tmp_w][3] = 1;
                    work_time += 4;
                }
                else if (tmp < 60)
                {
                    sche[tmp_w][1] = 1;
                    sche[tmp_w][2] = 1;
                    sche[tmp_w][3] = 1;
                    work_time += 3;
                }
                else
                {
                    sche[tmp_w][2] = 1;
                    sche[tmp_w][3] = 1;
                    work_time += 2;
                }
                cnt++;
                week[tmp_w] = 1;
            }
        }
        td[i].schedule = sche;
        td[i].work_time_sum = work_time;
    }

    return td;
}

void print_student_data(student sd)
{
    cout << "ID: " << sd.id << " ";
    cout << "[";
    rep(i, sd.subjects.size())
    {
        if (i != 0)
            cout << ", ";
        cout << sd.subjects[i];
    }
    cout << "]"
         << "  受講コマ数:" << sd.subjects_sum << endl;
}

void print_student_schedule_data(student sd)
{
    //cout << "受講可能時間帯" << endl;
    cout << "ID: " << sd.id << "  受講コマ数:" << sd.subjects_sum << endl;
    rep(i, 6)
    {
        cout << "Day" << i + 1 << " [";
        rep(j, 4)
        {
            if (j != 0)
                cout << ", ";
            cout << sd.schedule[i][j];
        }
        cout << "]" << endl;
    }
}

void print_student_compatibility(student sd)
{
    cout << "ID: " << sd.id << " [";
    rep(i, sd.compatibility.size())
    {
        if (i != 0)
            cout << ", ";
        cout << sd.compatibility[i];
    }
    cout << "]" << endl;
}

void print_teacher_available_subjects(teacher td)
{
    cout << "ID: " << td.id << " subjects [";
    rep(i, td.available_subjects.size())
    {
        if (i != 0)
            cout << ", ";
        cout << td.available_subjects[i];
    }
    cout << "]" << endl;
}

void print_teacher_schedule_data(teacher td)
{
    //cout << "出勤可能時間帯" << endl;
    cout << "ID: " << td.id << endl;
    rep(i, 6)
    {
        cout << "Day" << i + 1 << " [";
        rep(j, 4)
        {
            if (j != 0)
                cout << ", ";
            cout << td.schedule[i][j];
        }
        cout << "]" << endl;
    }
}

void print_teacher_work_sum(vector<teacher> td)
{
    int sum = 0;
    rep(i, num_of_teachers)
    {
        sum += td[i].work_time_sum;
    }
    cout << "総授業可能数: " << sum << endl;
}

void cplex_input_data(vector<student> sd, vector<teacher> td)
{

    //cout << endl << "CPLEX用" << endl;

    cout << "student = " << num_of_students << ";" << endl;
    cout << "teacher = " << num_of_teachers << ";" << endl;
    cout << "curriculum = 7;" << endl;
    cout << "date = 6;" << endl;
    cout << "period = 4;" << endl;

    //b:授業数
    cout << "b = " << endl
         << "[" << endl;
    rep(i, num_of_students)
    {
        cout << "    [";
        rep(j, sd[i].subjects.size())
        {
            if (j != 0)
                cout << " ";
            cout << sd[i].subjects[j];
        }
        cout << "] //" << i + 1 << endl;
    }
    cout << "];" << endl;

    //h:教えられる科目
    cout << "h = " << endl
         << "[" << endl;
    rep(i, num_of_teachers)
    {
        cout << "    [";
        rep(j, td[i].available_subjects.size())
        {
            if (j != 0)
                cout << " ";
            cout << td[i].available_subjects[j];
        }
        cout << "] //" << i + 1 << endl;
    }
    cout << "];" << endl;

    //c:アンケート結果
    cout << "c = " << endl
         << "[" << endl;
    rep(i, num_of_students)
    {
        cout << "    [";
        rep(j, sd[i].compatibility.size())
        {
            if (j != 0)
                cout << " ";
            cout << sd[i].compatibility[j];
        }
        cout << "] //" << i + 1 << endl;
    }
    cout << "];" << endl;

    //f:出勤可能な時限
    cout << "F = " << endl
         << "[" << endl;
    rep(i, num_of_teachers)
    {
        cout << "    [" << endl;
        rep(j, 6)
        {
            cout << "        [";
            rep(k, 4)
            {
                if (k != 0)
                    cout << " ";
                cout << td[i].schedule[j][k];
            }
            cout << "]" << endl;
        }
        cout << "    ] //" << i + 1 << endl;
    }
    cout << "];" << endl;

    //g:来塾可能な時限
    cout << "G = " << endl
         << "[" << endl;
    rep(i, num_of_students)
    {
        cout << "    [" << endl;
        rep(j, 6)
        {
            cout << "        [";
            rep(k, 4)
            {
                if (k != 0)
                    cout << " ";
                cout << sd[i].schedule[j][k];
            }
            cout << "]" << endl;
        }
        cout << "    ] //" << i + 1 << endl;
    }
    cout << "];" << endl;

    cout << "e = 15;" << endl;
}

void output_student_csv(vector<student> sd)
{
    rep(i, num_of_students)
    {
        cout << sd[i].id << ", ";
        int tmp = sd[i].id / 1000;
        if (tmp == 1)
        {
            cout << "高3";
        }
        else if (tmp == 2)
        {
            cout << "高2";
        }
        else if (tmp == 3)
        {
            cout << "高1";
        }
        else if (tmp == 4)
        {
            cout << "中3";
        }
        else if (tmp == 5)
        {
            cout << "中2";
        }
        else if (tmp == 6)
        {
            cout << "中1";
        }
        else if (tmp == 7)
        {
            cout << "小6";
        }
        else if (tmp == 8)
        {
            cout << "小5";
        }
        else if (tmp == 9)
        {
            cout << "小4";
        }
        cout << ", ";
        rep(j, sd[i].subjects.size())
        {
            if (j != 0)
                cout << ", ";
            cout << sd[i].subjects[j];
        }
        cout << endl;
    }
}

void csv_sd_schedule (vector<student> sd) {
    rep(i, num_of_students) {
        rep(j, 6) {
            if(j != 0) cout << ": ";
            vector<int> tmp = {1,1,1,1};
            if(sd[i].schedule[j] == tmp) {
                cout << "1,2,3,4";
                continue;
            }
            tmp = {0,1,1,1};
            if(sd[i].schedule[j] == tmp) {
                cout << "2,3,4";
                continue;
            } 
            tmp = {0,0,1,1};
            if(sd[i].schedule[j] == tmp) {
                cout << "3,4";
                continue;
            }
            tmp = {0,0,0,1};
            if(sd[i].schedule[j] == tmp) {
                cout << "4";
            }
            tmp = {1,1,0,0};
            if(sd[i].schedule[j] == tmp) {
                cout << "1,2";
            }      
        }
        cout << endl;
    }
}

void csv_compatibility(vector<student> sd) {
    rep(i, num_of_students) {
        rep(j, num_of_teachers) {
            if(j!=0) cout << ", ";
            cout << sd[i].compatibility[j];
        }
        cout << endl;
    }
}

void csv_td_schedule(vector<teacher> td) {
    rep(i, num_of_teachers) {
        rep(j, 6) {
            if(j != 0) cout << ": ";
            vector<int> tmp = {1,1,1,1};
            if(td[i].schedule[j] == tmp) {
                cout << "1,2,3,4";
            }
            tmp = {0,1,1,1};
            if(td[i].schedule[j] == tmp) {
                cout << "2,3,4";
            }
            tmp = {0,0,1,1};
            if(td[i].schedule[j] == tmp) {
                cout << "3,4";
                continue;
            }
            tmp = {0,0,0,1};
            if(td[i].schedule[j] == tmp) {
                cout << "4";
            }            
        }
        cout << endl;
    }
}

void csv_td_subject(vector<teacher> td) {
    rep(i, num_of_teachers) {
        rep(j, td[i].available_subjects.size()) {
            if(j != 0) cout << ", ";
            cout << td[i].available_subjects[j];
        }
        cout << endl;
    }
}


int main()
{

    vector<student> sd = make_student_data();
    vector<teacher> td = make_teacher_data();

    /*
    rep(i, num_of_students)
    {
        print_student_data(sd[i]);
    }

    cout << "受講可能時間帯" << endl;
    rep(i, num_of_students)
    {
        print_student_schedule_data(sd[i]);
    }
    calc_sum_classes(sd);

    cout << "アンケート結果" << endl;
    rep(i, num_of_students)
    {
        print_student_compatibility(sd[i]);
    }

    rep(i, num_of_teachers)
    {
        print_teacher_available_subjects(td[i]);
    }

    cout << "出勤可能時間帯" << endl;
    rep(i, num_of_teachers)
    {
        print_teacher_schedule_data(td[i]);
    }

    print_teacher_work_sum(td);

    //calc_sum_classes(sd);

    //print_teacher_work_sum(td);

    //cplex_input_data(sd, td);
    */

    //output_student_csv(sd);

    //csv_sd_schedule(sd);

    //csv_compatibility(sd);

    //csv_td_schedule(td);

    csv_td_subject(td);
}