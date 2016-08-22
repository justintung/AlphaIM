/*
 * Convert xml file to  AlphaDictionary.
 *
 * See Doc/dictionary_inner.pdf for more inner format detail.
 *
 * Changes:
 * 11-Nov-2013, initial version: [LiQiong lee]
 *
 */

#ifdef WIN32
#include <Windows.h>
#include <mbctype.h>
#endif
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <locale.h>
#include <unistd.h>

#include <string>
#include <vector>


#ifdef WIN32
#include "win32/pgetopt.h"
#endif

#include "type.h"
#include "Util.h"

#include "PinyinTDFParser.h"

using namespace std;

#define VERSION     "0.1"

//#define INDEX_BLOCK_NR   2
//#define STRINX_WORDS_MAX 10
//#define STRINX_DEPTH_MAX 5
//#define CHRINX_DEPTH_MIN 1
//#define STRINX_LEN_MAX   60  /* a string index must be within a block. */

static void usage()
{
    printf("Usage: AIMTool [options] \n");
    printf("options:");
    printf("    -h help\n");
    printf("    -v version\n");
    printf("    -p map db  :create PY database \n");
    printf("       For example:\n");
    printf("       -p system/pinyin.tdf  system/pinyin.imdb \n");
}

static void make_pinyinDB(const string& pinyinPath, const string& dbPath);

int main(int argc, char* argv[])
{
	int c;

#ifdef _LINUX
	setlocale(LC_ALL, "C.UTF-8");
#endif
    //Util::getTimeMS();

	while (( c = getopt(argc, argv, "hvp:")) != -1) {
	    switch (c) {
	    case 'h':
	    	usage();
            return 0;

        case 'v':
            printf("version: %s\n", VERSION);
            return 0;

	    case 'p':
            if (argc ==  4) {
                make_pinyinDB(optarg, argv[3]);
                return 0;
            }
            usage();
            return 0;
	    }
	}

    usage();
    return 0;
}

static void make_pinyinDB(const string& pinyinPath, const string& dbPath)
{
    PinyinTDFParser pyParser;
    //pyParser.setDbPath(dbPath);
    Util::getTimeMS();

    pyParser.parser(pinyinPath);
    pyParser.write(dbPath);

    printf("write db file, done: \n");
    printf("    entries: %u\n", pyParser.getTotalEntry());
    printf("    costs: (%u)s:(%u)ms\n", Util::getTimeMS()/1000, Util::getTimeMS()%1000);
}
