//
// Created by Ismail Shalanfeh on 12/7/24.
//

#ifndef SORTS_H
#define SORTS_H

#include <vector>

using namespace std;

class sorts {
    public:
        static void BubbleSort(vector<int> &Victim, int Start, int End);
        static void InsertionSort(vector<int> &Victim, int Start, int End);
        static void MergeSort(vector<int> &Victim, int Start, int End);
        static void IterativeMergeSort(vector<int> &Victim, int Start, int End);
        static void QuickSort(vector<int> &Victim, int Start, int End);
        static void ShellSort(vector<int> &Victim, int Start, int End);

    private:
};

//Universal base cases:
//1) Vector.size < 2 (1 or 0 elements present)
//2) start is end
//Probably should have done this in sorter.cpp... too late now lol

//Helper functions

//I should have just taken Start and End as the parameters
//The index pairs are always next to each other :/
void Merge(vector<int> &Victim, int Start1, int End1, int Start2, int End2) {
    //Make sure the index's will work
    if (!((Start1 <= End1) && (Start2 <= End2))) {
        return;
    }

    //Surprise magic for later
    int OGStart1 = Start1;

    vector<int> Temp;

    //Merge into temp
    while ((Start1 <= End1) && (Start2 <= End2)) {
        if (Victim[Start1] <= Victim[Start2]) {
            Temp.push_back(Victim[Start1]);
            Start1 += 1;
        } else {
            Temp.push_back(Victim[Start2]);
            Start2 += 1;
        }
    }

    //Insert remaining start1
    while (Start1 <= End1) {
        Temp.push_back(Victim[Start1]);
        Start1 += 1;
    }

    //Insert remaining start2
    while (Start2 <= End2) {
        Temp.push_back(Victim[Start2]);
        Start2 += 1;
    }

    copy(Temp.begin(), Temp.end(), Victim.begin() + OGStart1);
}

int Parition(vector<int> &Victim, int Start, int End) {
    //Set pivot to the middle index
    int PivotIndex = Start + (End - Start) / 2;
    int PivotValue = Victim[PivotIndex];

    //Move pivot to the end
    swap(Victim[PivotIndex], Victim[End]);

    //Move values accordingly
    for (int i = Start; i < End; ++i) {
        if (Victim[i] < PivotValue) {
            swap(Victim[i], Victim[Start]);
            Start++;
        }
    }

    //Put pivoted value in correct position
    swap(Victim[Start], Victim[End]);
    return Start;
}

//Implementation

//N^2 Iterative sort
void sorts::BubbleSort(vector<int> &Victim, int Start, int End) {
    //Case where vector sorted or empty
    if (Victim.size() < 2) {
        return;
    }

    //Case where start is end
    if (Start == End) {
        return;
    }

    //Bubble up N amount of times
    for (int i = 0; i < End; i++) {

        //Variable for early completion
        bool Swapped = false;

        for (int j = 0; j < End - i; j++) {
            //Check if current and next value need to be bubbled
            if (Victim[j] > Victim[j + 1]) {
                swap(Victim[j], Victim[j + 1]);
                Swapped = true;
            }
        }

        if (!Swapped) {
            return;
        }
    }
}

void sorts::InsertionSort(vector<int> &Victim, int Start, int End) {
    //Case where vector sorted or empty
    if (Victim.size() < 2) {
        return;
    }

    //Case where start is end
    if (Start == End) {
        return;
    }

    //The sorting
    for (int i = 1; i < Victim.size(); i++) {
        int j = i;
        while ((j > 0) && (Victim[j - 1] > Victim[j])) {
            swap(Victim[j], Victim[j - 1]);
            j -= 1;
        }
    }
}

void sorts::MergeSort(vector<int> &Victim, int Start, int End) {
    //Case where vector sorted or empty
    if (Victim.size() < 2) {
        return;
    }

    //Case where start is end (normal for this one)
    if (Start == End) {
        return;
    }

    int mid = Start + (End - Start) / 2;

    MergeSort(Victim, Start, mid);
    MergeSort(Victim, mid + 1, End);

    Merge(Victim, Start, mid, mid + 1, End);
}

void sorts::IterativeMergeSort(vector<int> &Victim, int Start, int End) {
    if (Victim.size() < 2) {
        return;
    }
    if (Start == End) {
        return;
    }

    int MainSize = Victim.size();

    //Traverse in pairs
    for (int PairSize = 1; PairSize < MainSize; PairSize *= 2) {

        //Traverse two pairs at a time
        //Pair1 is the index of the first pair being looped on
        for (int Pair1 = 0; Pair1 < MainSize - 1; Pair1 += 2 * PairSize) {
            //Min because of out of bounds shenanigans
            int End1 = min(Pair1 + PairSize - 1, MainSize - 1); //End of pair1

            //Check if it's possible for a second pair to exist
            if (End1 == MainSize - 1) {
                break;
            }

            int Start2 = min(End1 + 1, MainSize - 1); //Start of pair2
            int End2  = min(Pair1 + 2 * PairSize - 1, MainSize - 1); //End of pair2

            //Merge them in mergesort fashion
            Merge(Victim, Pair1, End1, Start2, End2);
        }
    }

}

void sorts::QuickSort(vector<int> &Victim, int Start, int End) {
    if (Victim.size() < 2) {
        return;
    }
    if (Start == End) {
        return;
    }
    if (Start < End) {
        int PPoint = Parition(Victim, Start, End);
        QuickSort(Victim, Start, PPoint - 1);
        QuickSort(Victim, PPoint + 1, End);
    }
}

//This one scares me
void sorts::ShellSort(vector<int> &Victim, int Start, int End) {
    if (Victim.size() < 2) {
        return;
    }
    if (Start == End) {
        return;
    }

    int Size = Victim.size();
    int Gap = Size / 2;

    while (!(Gap <= 1)) {
        int Current = Start;
        while (Current + Gap <= End) {
            if (Victim[Current] > Victim[Current + Gap]) {
                swap(Victim[Current], Victim[Current + Gap]);

                int TempCurrent = Current;
                int BackTrack = Current - Gap;
                while (BackTrack >= 0) {
                    if (Victim[TempCurrent] < Victim[BackTrack]) {
                        swap(Victim[TempCurrent], Victim[BackTrack]);
                        TempCurrent -= Gap;
                        BackTrack -= Gap;
                    } else {
                        break;
                    }
                }

            }
            Current += 1;
        }
        Gap /= 2;
    }
    InsertionSort(Victim, Start, End);
}


#endif //SORTS_H
