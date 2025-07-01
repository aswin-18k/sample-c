#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_OPTION_LEN 100
#define MAX_NAME_LEN 50
#define TIME_LIMIT 10

typedef struct {
    char question[256];
    char options[4][MAX_OPTION_LEN];
    int correctOption; // 1-based index
} Question;

Question questions[MAX_QUESTIONS] = {
    {
        "What is the capital of France?",
        {"Berlin", "Madrid", "Paris", "Rome"},
        3
    },
    {
        "Which planet is known as the Red Planet?",
        {"Earth", "Mars", "Jupiter", "Saturn"},
        2
    },
    {
        "What is 5 + 3?",
        {"6", "7", "8", "9"},
        3
    },
    {
        "Which language is used for system programming?",
        {"Python", "Java", "C", "HTML"},
        3
    },
    {
        "Who wrote 'Romeo and Juliet'?",
        {"Shakespeare", "Hemingway", "Tolkien", "Austen"},
        1
    }
};

void shuffleQuestions() {
    for (int i = 0; i < MAX_QUESTIONS; i++) {
        int j = rand() % MAX_QUESTIONS;
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void saveHighScore(const char *name, int score) {
    FILE *file = fopen("highscores.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s: %d/%d\n", name, score, MAX_QUESTIONS);
        fclose(file);
        printf("Score saved successfully!\n");
    } else {
        printf("Failed to save score.\n");
    }
}

void startQuiz() {
    int answer, score = 0;
    char name[MAX_NAME_LEN];
    time_t start, end;

    shuffleQuestions();

    printf("\n--- Quiz Started! ---\n");

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        printf("\nQ%d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, questions[i].options[j]);
        }

        printf("You have %d seconds to answer...\n", TIME_LIMIT);
        time(&start);
        printf("Enter your answer (1-4): ");

        if (scanf("%d", &answer) != 1) {
            clearInputBuffer();
            printf("Invalid input! Skipping question.\n");
            continue;
        }

        time(&end);
        double timeTaken = difftime(end, start);

        if (timeTaken > TIME_LIMIT) {
            printf("⏱ Time's up! You took %.0f seconds.\n", timeTaken);
            continue;
        }

        if (answer < 1 || answer > 4) {
            printf("Invalid option. Skipping question.\n");
            continue;
        }

        if (answer == questions[i].correctOption) {
            printf("✅ Correct!\n");
            score++;
        } else {
            printf("❌ Wrong! Correct answer: %s\n", questions[i].options[questions[i].correctOption - 1]);
        }
    }

    printf("\n--- Quiz Completed! ---\n");
    printf("Your score: %d out of %d\n", score, MAX_QUESTIONS);

    if (score == MAX_QUESTIONS)
        printf("🎉 Excellent!\n");
    else if (score >= 3)
        printf("👍 Good job!\n");
    else
        printf("🙁 Try again!\n");

    printf("Enter your name to save the score: ");
    scanf("%s", name);
    saveHighScore(name, score);
}

int main() {
    srand(time(NULL)); // Initialize random seed
    startQuiz();
    return 0;
}
