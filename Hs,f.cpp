#include <iostream>
#include <vector>
#include <string>
#include <chrono> // Для работы с датами

using namespace std;

class Tournament {
private:
    string name;
    string location;
    int year;
    string winner;
    chrono::system_clock::time_point start_date;
    chrono::system_clock::time_point end_date;
    vector<string> participants; // Вектор участников турнира

public:
    Tournament(string n, string l, int y, string w, chrono::system_clock::time_point start, chrono::system_clock::time_point end)
        : name(n), location(l), year(y), winner(w), start_date(start), end_date(end) {}

    void displayInfo() const {
        cout << "-------------------------------\n";
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Year: " << year << endl;
        cout << "Winner: " << winner << endl;
        cout << "Start Date: " << chrono::system_clock::to_time_t(start_date) << endl;
        cout << "End Date: " << chrono::system_clock::to_time_t(end_date) << endl;
        cout << "Participants: " << participants.size() << endl; // Выводим количество участников
        cout << "-------------------------------\n";
    }

    // Методы для работы с участниками турнира

    void addParticipant(const string& participant) {
        participants.push_back(participant);
    }

    const vector<string>& getParticipants() const {
        return participants;
    }

    string getName() const {
        return name;
    }

    chrono::system_clock::time_point getStartDate() const {
        return start_date;
    }

    chrono::system_clock::time_point getEndDate() const {
        return end_date;
    }
};

class Database {
private:
    vector<Tournament> tournaments;

public:
    void addTournament(const Tournament& tournament) {
        tournaments.push_back(tournament);
    }
    void registerParticipant(const string& tournamentName, const string& participantName) {
        for (auto& tournament : tournaments) {
            if (tournament.getName() == tournamentName) {
                tournament.addParticipant(participantName);
                cout << "Participant " << participantName << " registered for tournament " << tournamentName << endl;
                return;
            }
        }
        cout << "Tournament " << tournamentName << " not found." << endl;
    }
    
    void displayAllTournaments() const {
        cout << "All Tournaments:\n";
        for (const auto& tournament : tournaments) {
            tournament.displayInfo();
        }
    }

    void displayPastTournaments() const {
        cout << "Past Tournaments:\n";
        chrono::system_clock::time_point now = chrono::system_clock::now();
        for (const auto& tournament : tournaments) {
            if (tournament.getEndDate() < now) {
                tournament.displayInfo();
            }
        }
    }

    void displayOngoingTournaments() const {
        cout << "Ongoing Tournaments:\n";
        chrono::system_clock::time_point now = chrono::system_clock::now();
        for (const auto& tournament : tournaments) {
            if (tournament.getStartDate() <= now && tournament.getEndDate() >= now) {
                tournament.displayInfo();
            }
        }
    }

    void displayFutureTournaments() const {
        cout << "Future Tournaments:\n";
        chrono::system_clock::time_point now = chrono::system_clock::now();
        for (const auto& tournament : tournaments) {
            if (tournament.getStartDate() > now) {
                tournament.displayInfo();
            }
        }
    }
};

int main() {
    Database database;

    // Пример добавления турниров в базу данных
    // Для примера используем текущую дату и время
    chrono::system_clock::time_point now = chrono::system_clock::now();
    chrono::system_clock::time_point past_date = now - chrono::hours(24 * 30); // Пример прошедшей даты: 30 дней назад
    chrono::system_clock::time_point future_date = now + chrono::hours(24 * 30); // Пример будущей даты: через 30 дней
    Tournament t1("Bass Fishing Championship", "Lake Michigan", 2023, "John Smith", past_date, past_date + chrono::hours(48));
    Tournament t2("Trout Anglers Cup", "Yellowstone River", 2022, "Emily Johnson", now - chrono::hours(12), now + chrono::hours(12));
    Tournament t3("Salmon Masters", "Alaska", 2024, "", future_date, future_date + chrono::hours(72));
    Tournament t4("Deep Sea Fishing Tournament", "Gulf of Mexico", 2023, "Michael Rodriguez", past_date, past_date + chrono::hours(36));
    Tournament t5("Fly Fishing Classic", "Big Horn River", 2022, "Sophia Lee", now - chrono::hours(6), now + chrono::hours(6));
    Tournament t6("Ice Fishing Challenge", "Lake Superior", 2024, "", future_date, future_date + chrono::hours(48));

    database.addTournament(t1);
    database.addTournament(t2);
    database.addTournament(t3);
    database.addTournament(t4);
    database.addTournament(t5);
    database.addTournament(t6);

    int choice;

    do {
        cout << "---------------------------------\n";
        cout << "            Main Menu\n";
        cout << "---------------------------------\n";
        cout << "1. Display All Tournaments\n";
        cout << "2. Display Past Tournaments\n";
        cout << "3. Display Ongoing Tournaments\n";
        cout << "4. Display Future Tournaments\n";
        cout << "5. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            database.displayAllTournaments();
            break;
        case 2:
            database.displayPastTournaments();
            break;
        case 3:
            database.displayOngoingTournaments();
            break;
        case 4:
            database.displayFutureTournaments();
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}