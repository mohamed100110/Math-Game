#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct stfinish_result
{
    int count_right_answer;
    int count_wrong_answer;
    int number_of_qustion;
    string name_level;
    string type_operation;

};
enum enlevel_question { easy = 1, mid, hard, mix };
enum encheck_answer { right, wrong };
int read_num_positive(string m)
{
    int n;
    do
    {
        cout << m;
        cin >> n;
    } while (n <= 0);
    return n;
}
int read_num_in_range(int from, int to, string m)
{
    int n;
    do
    {
        cout << m;
        cin >> n;
    } while (n < from || n > to);
    return n;
}
int random_number_in_range(int from, int to)
{
    return rand() % (to - from + 1) + from;
}
void reset_screen()
{
    system("color 0F");
    system("cls");
}
struct stgame_info
{
    int how_question;
    int level_question;
    int type_question;
};
string get_name_level(int n)
{
    string arrlevel[4] = { "easy","mid","hard","mix" };
    return arrlevel[n - 1];

}
string get_name_operation(int n)
{
    string arroperation[5] = { "add","sub","mul","div","mix"};
    return arroperation[n - 1];
}
struct stquestion_info
{
    int random1;
    int random2;
    int answer;
};
stgame_info func_game_info()
{
    stgame_info game_info;
    game_info.how_question = read_num_positive("How many questions do you want to answer ? ");

    game_info.level_question = read_num_in_range(1, 4, "Enter question level [1] easy,[2] mid,[3] hard,[4] mix ? ");

   

    game_info.type_question = read_num_in_range(1, 5, "Enter question type [1] add,[2] sub,[3] mul,[4] div,[5] mix ? ");
   
    cout << "\n";
    return game_info;
}
char choice_type_operation(int n)
{
    char arrchar[4] = { '+','-','*','/' };
    return arrchar[n - 1];
}
stquestion_info get_2random_number( int level_question)
{
    stquestion_info info_question;

    if (level_question == enlevel_question::easy)
    {
        info_question.random1 = random_number_in_range(1, 10);
        info_question.random2 = random_number_in_range(1, 10);
    }
    else if (level_question == enlevel_question::mid)
    {
        info_question.random1 = random_number_in_range(10, 50);
        info_question.random2 = random_number_in_range(10, 50);
    }
    else
    {
        info_question.random1 = random_number_in_range(50, 100);
        info_question.random2 = random_number_in_range(50, 100);
    }
    return info_question;
}
stquestion_info form_of_question(char type_operation, int level_question)
{
    stquestion_info info_question;
    info_question = get_2random_number(level_question);
    cout << info_question.random1;
    cout << "   " << type_operation << endl;
    cout << info_question.random2;
    cout << "\n____________________\n";
    cin >> info_question.answer;
    return info_question;
}
int the_real_answer(char type_operation, stquestion_info info)
{

    switch (type_operation)
    {
    case '+':
        return info.random1 + info.random2;
    case '-':
        return info.random1 - info.random2;
    case '*':
        return info.random1 * info.random2;
    case '/':
        return info.random1 / info.random2;
    default :
        return info.random1 + info.random2;
    }
}
encheck_answer check_answer(int answer, int the_real_answer)
{
    if (answer == the_real_answer)
        return encheck_answer::right;
    else
        return encheck_answer::wrong;

}
void color_of_screen(encheck_answer answer)
{
    if (answer == encheck_answer::right)
    {

        system("color 2F");
    }
    else
    {
        cout << "\a";
        system("color 4F");
    }
}
stfinish_result full_finish_result(stgame_info game_info, int right_answer, int wrong_answer)
{
    stfinish_result finish_result;
    finish_result.count_right_answer = right_answer;
    finish_result.count_wrong_answer = wrong_answer;
    finish_result.number_of_qustion = game_info.how_question;
    finish_result.name_level = get_name_level(game_info.level_question);
    finish_result.type_operation = get_name_operation(game_info.type_question);
    return finish_result;
}
encheck_answer pass_or_fail(stfinish_result finish_result)
{
    if (finish_result.count_right_answer >= finish_result.count_wrong_answer)
        return encheck_answer::right;
    else
        return encheck_answer::wrong;

}
void print_finish_result(encheck_answer pass_or_fail, stfinish_result finish_result)
{
    string statues;
    if (pass_or_fail == encheck_answer::right)
        statues = "PASS :-)";
    else
        statues = "FAIL :-(";

    cout << "\n____________________________\n\n";
    cout << "Final results is " << statues << endl;
    cout << "____________________________\n\n";
    cout << "number of questions :" << finish_result.number_of_qustion << endl;
    cout << "questions level     :" << finish_result.name_level << endl;
    cout << "operation type      :" << finish_result.type_operation << endl;
    cout << "number of right answers:" << finish_result.count_right_answer << endl;
    cout << "number of wrong answers:" << finish_result.count_wrong_answer << endl;
    cout << "____________________________\n\n";
    color_of_screen(pass_or_fail);

}
void func_mix(stgame_info &game_info)
{
    if (game_info.level_question == enlevel_question::mix)
    {
        game_info.level_question = random_number_in_range(1, 3);
    }
    if (game_info.type_question == 5)
    {
        game_info.type_question = random_number_in_range(1, 4);
    }
   
}
stfinish_result play_game(stgame_info game_info)
{
    int right_answer = 0, wrong_answer = 0;
    stgame_info temp = game_info;
    for (int i = 1; i <= game_info.how_question; i++)
    {
        cout << "question [" << i << "/" << game_info.how_question << "]\n\n";
        func_mix(game_info);
        char type_operation = choice_type_operation(game_info.type_question);
        stquestion_info info_question = form_of_question(type_operation,game_info.level_question);
        int real_answer = the_real_answer(type_operation, info_question);
        encheck_answer result_check = check_answer(info_question.answer, real_answer);
        if (result_check == encheck_answer::right)
        {
            right_answer++;
            cout << "right answer :-)" << "\n\n\n";
        }
        else
        {
            wrong_answer++;
            cout << "wrong answer :-(" << endl;
            cout << "the real answer = " << real_answer << "\n\n\n";
        }
        color_of_screen(result_check);
        game_info = temp;
    }
    return full_finish_result(game_info, right_answer, wrong_answer);
}
void start_game()
{
    char play_again = 'y';
    do
    {
        reset_screen();
        stfinish_result finish_result = play_game(func_game_info());
        print_finish_result(pass_or_fail(finish_result), finish_result);

        cout << "Do you want to play again ?(Y/N)" << endl;
        cin >> play_again;
    } while (play_again == 'y' || play_again == 'Y');
}
int main()
{

    srand((unsigned)time(NULL));
    start_game();



}