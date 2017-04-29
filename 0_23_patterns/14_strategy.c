typedef struct _MoviePlay
{
    struct _CommonMoviePlay* pCommonMoviePlay;
} MoviePlay;

typedef struct _CommonMoviePlay {
    HANDLE hFile;
    void (*play)(HANDLE hFile);
} CommonMoviePlay;

// a single interface
void play_movie_file(struct _MoviePlay* pMoviePlay)
{
    CommonMoviePlay* pCommonMoviePlay;
    assert(NULL !pMoviePlay);

    pCommonMoviePlay = pMoviePlay->pCommonMoviePlay;
    pCommonMoviePlay->play(pCommonMoviePlay->hFile);
}

//----------
void play_avi_file(HANDLE file)
{
    printf("play avi file!\n");
}

void play_rmvb_file(HANDLE file)
{
    printf("play rmvb file!\n");
}

void play_mpeg_file(HANDLE file)
{
    printf("play mpeg file!\n");
}
