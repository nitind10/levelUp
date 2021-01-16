//queen problems

//combination of queens in boxes (1D)
int queensInBoxes1DCombinations(int boxes, int queens, int currBox, int currQueen, string ans){

    if(currQueen == queens){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        count += queensInBoxes1DCombinations(boxes, queens, i + 1, currQueen + 1, ans + "b" + to_string(i) + "q" + to_string(currQueen));
    }
    return count;
}

//permutations of queens in boxes (1D)
int queensInBoxes1DPermutations(int boxes, int queens, int currBox, int currQueen, string ans, vector<bool>& visited){

    if(currQueen == queens){
        cout << ans << endl;
        return 1;
    }
    int count = 0;
    for(int i = currBox; i < boxes; ++i){
        if(!visited[i]){
            visited[i] = true;
            count += queensInBoxes1DPermutations(boxes, queens, 0, currQueen + 1, ans + "b" + to_string(i) + "q" + to_string(currQueen), visited);
            visited[i] = false;
        }
    }
    return count;
}