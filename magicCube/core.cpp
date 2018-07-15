#include "core.h"

char faces_[] ="RLFBU";
char order_[] ="AECGBFDHIJKLMSNTROQP";
char bithash_[] = "TdXhQaRbEFIJUZfijeYV";
char perm_[] = "AIBJTMROCLDKSNQPEKFIMSPRGJHLNTOQAGCEMTNSBFDHORPQ";

char pos[20], ori[20], val[20],
     *tables[8];              //此为初始化table内容
int move_[20], moveamount[20],
phase = 0,
tablesize[] = { 1,4096, 6561,4096,256,1536,  13824,576 };
int TEMP;


core::core()
{

}

void core::table_Init(){

//这里的数据全部重新初始化
    faces=faces_;
    order = order_;
    bithash = bithash_;
    perm = perm_;

    memset(pos,0,sizeof(pos)/sizeof(char));
    memset(ori,0,sizeof(ori)/sizeof(char));
    memset(val,0,sizeof(val)/sizeof(char));


    memset(move_,0,sizeof(move_)/sizeof(int));
    memset(moveamount,0,sizeof(moveamount)/sizeof(int));
    phase = 0;

    //这里table 初始化
    for (int k =0; k<20; k++) val[k] = k<12 ? 2 : 3;
    for (int j=0; j<8; j++) filltable(j);

}
QString core::core_caculate(std::string get[]){

    int f =0,k =0,i=0,j=0,pc,mor;
    QString answer_out;

    table_Init();

    for (i=0; i<20; i++) {

        f = pc = k = mor = 0;
        for (; f<val[i]; f++) {

            j = myfind(get[i][f]);         //这里输入

            if (j>k) { k = j; mor = f; }

            pc += 1 << j;
        }

        for (f = 0; f<20; f++)
            if (pc == bithash[f] - 64) break;

        pos[order[i] - CHAROFFSET] = f;
        ori[order[i] - CHAROFFSET] = mor%val[i];
    }


    for (; phase<8; phase += 2) {
        // try each depth till solved
        for (j = 0; !searchphase(j, 0, 9); j++);
        //output result of this phase
        for (i = 0; i < j; i++) {
            QString tmp = QString("FBRLUD"[move_[i]])+QString::number(moveamount[i])/*+" "*/; //这里进行输出
            answer_out+=tmp;
        }
    }

    return answer_out;

}


void core::cycle(char*p, char*a){

    SWAP(p[*a - CHAROFFSET], p[a[1] - CHAROFFSET]);
    SWAP(p[*a - CHAROFFSET], p[a[2] - CHAROFFSET]);
    SWAP(p[*a - CHAROFFSET], p[a[3] - CHAROFFSET]);

}

void core::twist(int i, int a) {
    i -= CHAROFFSET;
    ori[i] = (ori[i] + a + 1) % val[i];
}


void core::reset() {

    for (int i = 0; i<20; pos[i] = i, ori[i++] = 0);
}

int core::permtonum(char* p) {
    int n = 0;
    for (int a = 0; a<4; a++) {
        n *= 4 - a;
        for (int b = a; ++b<4; )
            if (p[b]<p[a]) n++;
    }
    return n;
}

void core::numtoperm(char* p, int n, int o) {
    p += o;
    p[3] = o;
    for (int a = 3; a--;) {
        p[a] = n % (4 - a) + o;
        n /= 4 - a;
        for (int b = a; ++b<4; )
            if (p[b] >= p[a]) p[b]++;
    }

}


int core::getposition(int t) {
    int i = -1, n = 0;
    switch (t) {
        // case 0 does nothing so returns 0
    case 1://edgeflip
           // 12 bits, set bit if edge is flipped
        for (; ++i<12;) n += ori[i] << i;
        break;
    case 2://cornertwist
           // get base 3 number of 8 digits - each digit is corner twist
        for (i = 20; --i>11;) n = n * 3 + ori[i];
        break;
    case 3://middle edge choice
           // 12 bits, set bit if edge belongs in Um middle slice
        for (; ++i<12;) n += (pos[i] & 8) ? (1 << i) : 0;
        break;
    case 4://ud slice choice
           // 8 bits, set bit if UD edge belongs in Fm middle slice
        for (; ++i<8;) n += (pos[i] & 4) ? (1 << i) : 0;
        break;
    case 5://tetrad choice, twist and parity
        int corn[8], j, k, l, corn2[4];
        // 8 bits, set bit if corner belongs in second tetrad.
        // also separate pieces for twist/parity determination
        k = j = 0;
        for (; ++i<8;)
            if ((l = pos[i + 12] - 12) & 4) {
                corn[l] = k++;
                n += 1 << i;
            }
            else corn[j++] = l;
            //Find permutation of second tetrad after solving first
            for (i = 0; i<4; i++) corn2[i] = corn[4 + corn[i]];
            //Solve one piece of second tetrad
            for (; --i;) corn2[i] ^= corn2[0];

            // encode parity/tetrad twist
            n = n * 6 + corn2[1] * 2 - 2;
            if (corn2[3]<corn2[2])n++;
            break;
    case 6://two edge and one corner orbit, permutation
        n = permtonum(pos) * 576 + permtonum(pos + 4) * 24 + permtonum(pos + 12);
        break;
    case 7://one edge and one corner orbit, permutation
        n = permtonum(pos + 8) * 24 + permtonum(pos + 16);
        break;
    }
    return n;
}


char corn[] ="QRSTQRTSQSRTQTRSQSTRQTSR";          //这里修改

void core::setposition(int t, int n) {

    int i = 0, j = 12, k = 0;
     temp_corn = corn;
    reset();
    switch (t) {
        // case 0 does nothing so leaves cube solved
    case 1://edgeflip
        for (; i<12; i++, n >>= 1) ori[i] = n & 1;
        break;
    case 2://cornertwist
        for (i = 12; i<20; i++, n /= 3) ori[i] = n % 3;
        break;
    case 3://middle edge choice
        for (; i<12; i++, n >>= 1) pos[i] = 8 * n & 8;
        break;
    case 4://ud slice choice
        for (; i<8; i++, n >>= 1) pos[i] = 4 * n & 4;
        break;
    case 5:    //tetrad choice,parity,twist
        temp_corn += n % 6 * 4;

        n /= 6;
        for (; i<8; i++, n >>= 1)
            pos[i + 12] = n & 1 ? temp_corn[k++] - CHAROFFSET : j++;
        break;
    case 6://slice permutations
        numtoperm(pos, n % 24, 12); n /= 24;
        numtoperm(pos, n % 24, 4); n /= 24;
        numtoperm(pos, n, 0);
        break;
    case 7://corner permutations
        numtoperm(pos, n / 24, 8);
        numtoperm(pos, n % 24, 16);
        break;
    }
}

void core::domove(int m) {
    char *p = perm + 8 * m, i = 8;
    //cycle the edges
    cycle(pos, p);
    cycle(ori, p);
    //cycle the corners
    cycle(pos, p + 4);
    cycle(ori, p + 4);
    //twist corners if RLFB
    if (m<4)
        for (; --i>3;) twist(p[i], i & 1);
    //flip edges if FB
    if (m<2)
        for (i = 4; i--;) twist(p[i], 0);
}

void core::filltable(int ti) {
    int n = 1, l = 1, tl = tablesize[ti];
    // alocate table memory
    char* tb = tables[ti] = new char[tl];
    //clear table
    memset(tb, 0, tl);
    //mark solved position as depth 1
    reset();
    tb[getposition(ti)] = 1;

    // while there are positions of depth l
    while (n) {
        n = 0;
        // find each position of depth l
        for (int i = 0; i<tl; i++) {
            if (tb[i] == l) {
                //construct that cube position
                setposition(ti, i);
                // try each face any amount
                for (int f = 0; f<6; f++) {
                    for (int q = 1; q<4; q++) {
                        domove(f);
                        // get resulting position
                        int r = getposition(ti);
                        // if move as allowed in that phase, and position is a new one
                        if ((q == 2 || f >= (ti & 6)) && !tb[r]) {
                            // mark that position as depth l+1
                            tb[r] = l + 1;
                            n++;
                        }
                    }
                    domove(f);
                }
            }
        }
        l++;
    }
}

bool core::searchphase(int movesleft, int movesdone, int lastmove) {
    // prune - position must still be solvable in the remaining moves available
    if (tables[phase][getposition(phase)] - 1 > movesleft ||
        tables[phase + 1][getposition(phase + 1)] - 1 > movesleft) return false;

    // If no moves left to do, we have solved this phase
    if (!movesleft) return true;

    // not solved. try each face move
    for (int i = 6; i--;) {
        // do not repeat same face, nor do opposite after DLB.
        if (i - lastmove && (i - lastmove + 1 || i | 1)) {
            move_[movesdone] = i;
            // try 1,2,3 quarter turns of that face
            for (int j = 0; ++j<4;) {
                //do move and remember it
                domove(i);
                moveamount[movesdone] = j;
                //Check if phase only allows half moves of this face
                if ((j == 2 || i >= phase) &&
                    //search on
                    searchphase(movesleft - 1, movesdone + 1, i)) return true;
            }
            // put face back to original position.
            domove(i);
        }
    }
    // no solution found
    return false;
}

int core::myfind(char a) {

    switch (a) {
    case 'R':
        return 0;
        break;
    case 'L':
        return 1;
        break;
    case 'F':
        return 2;
        break;
    case 'B':
        return 3;
        break;
    case 'U':
        return 4;
        break;
    case 'D':
        return 5;
        break;
    }
}






