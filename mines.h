class Board {
private:
    unsigned int rows, fields, mines;
    int **board = nullptr, **clicked = nullptr, **flagged = nullptr;

public:
    Board(int c, int r, int m);

    int getRows();

    int getColumns();

    int getMines();

    void buildBoard();

	void showBoard();

    void garbageDump();

    int click(int x, int y, bool flag);
};
