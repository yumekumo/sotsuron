/*********************************************
 * OPL 20.1.0.0 Model
 * Author: user
 * Creation Date: 2021/01/20 at 11:40:48
 *********************************************/
//using CP; 

execute{
	}
	
int student = ...;
int teacher = ...;
int curriculum = ...;
int date = ...;
int period = ...;
range S = 1..student;
range T = 1..teacher;
range U = 1..curriculum;
range D = 1..date;
range P = 1..period;
int b[S][U] = ...;
int h[T][U] = ...;
int c[S][T] = ...;
int F[T][D][P] = ...;
int G[S][D][P] = ...;
int e = ...;

dvar int x[T][S][U][D][P] in 0..1;
dvar int y[T][D][P] in 0..1;
dvar int z[T][D] in 0..1;
dvar int v[T][S][U] in 0..1;

maximize
  sum(s in S, t in T, u in U, d in D, p in P) x[t][s][u][d][p] * c[s][t];

subject to {
  forall(s in S, u in U) {
    sum(t in T, d in D, p in P) x[t][s][u][d][p] == b[s][u];
  }
  
  forall(d in D, p in P) {
    sum(t in T) y[t][d][p] <= e;
  }
  
  
  //ˆê‰ñ‚ÌŽö‹Æ‚Å2l‚ð’´‚¦‚é¶“k‚ðŽ‚½‚È‚¢
  forall(t in T, d in D, p in P) {
    sum(s in S, u in U) x[t][s][u][d][p] <= 2;
  }
  
  //¶“k‚ÌŠe‰È–Ú‚ÌŽö‹Æ‚Í‚¨‚È‚¶uŽt‚ª’S“–‚·‚é
  forall(s in S, u in U) {
    sum(t in T) v[t][s][u] <= 1;
  }
  
  
  forall(t in T, u in U, d in D, p in P) {
    sum(s in S) x[t][s][u][d][p] <= h[t][u];
  }

  forall(s in S, d in D, p in P) {
    sum(t in T, u in U) x[t][s][u][d][p] <= G[s][d][p];
  }
  forall(t in T, d in D, p in P) {
    y[t][d][p] <= F[t][d][p];
  }
  
  //‹ó‚«ƒRƒ}‚ðì‚ç‚È‚¢(uŽt)
  forall(t in T, d in D) {
    1000*y[t][d][1] + 100*y[t][d][2] + 10*y[t][d][3] + y[t][d][4] != 1001;
    1000*y[t][d][1] + 100*y[t][d][2] + 10*y[t][d][3] + y[t][d][4] != 1010;
	1000*y[t][d][1] + 100*y[t][d][2] + 10*y[t][d][3] + y[t][d][4] != 1011;
    1000*y[t][d][1] + 100*y[t][d][2] + 10*y[t][d][3] + y[t][d][4] != 1101;
	1000*y[t][d][1] + 100*y[t][d][2] + 10*y[t][d][3] + y[t][d][4] != 101;
  }
  //‹ó‚«ƒRƒ}‚ðì‚ç‚È‚¢(¶“k)
  forall(s in S, d in D) {
    sum(t in T, u in U) (1000*x[t][s][u][d][1] + 100*x[t][s][u][d][2] + 10*x[t][s][u][d][3] + x[t][s][u][d][4]) != 1001;
    sum(t in T, u in U) (1000*x[t][s][u][d][1] + 100*x[t][s][u][d][2] + 10*x[t][s][u][d][3] + x[t][s][u][d][4]) != 1010;
    sum(t in T, u in U) (1000*x[t][s][u][d][1] + 100*x[t][s][u][d][2] + 10*x[t][s][u][d][3] + x[t][s][u][d][4]) != 1011;
    sum(t in T, u in U) (1000*x[t][s][u][d][1] + 100*x[t][s][u][d][2] + 10*x[t][s][u][d][3] + x[t][s][u][d][4]) != 1101;
    sum(t in T, u in U) (1000*x[t][s][u][d][1] + 100*x[t][s][u][d][2] + 10*x[t][s][u][d][3] + x[t][s][u][d][4]) != 101;
  }
  
  
  forall(t in T, s in S, u in U, d in D, p in P) {
    x[t][s][u][d][p] <= y[t][d][p];
    y[t][d][p] <= z[t][d];
    x[t][s][u][d][p] <= v[t][s][u];
  }
  
};

execute printSchedule {
  for(var d = 1; d <= date; d++) {
    writeln("Day", d);
    for(var t = 1; t <= teacher; t++) {
      if(z[t][d] == 1) {
        writeln("Teacher", t)
        for(var p = 1; p <= period; p++) {
          write("period", p);
          for(var u = 1; u <= curriculum; u++) {
            for(var s = 1; s <= student; s++) {
              if(x[t][s][u][d][p] == 1) {
                if(u == 1) {
                  write("  Math");
                } 
                if(u == 2) {
                  write("  English");
                }
                if(u == 3) {
                  write("  Japanese");
                }
                if(u == 4) {
                  write("  Science");
                }
                if(u == 5) {
                  write("  Social");
                }
                if(u == 6) {
                  write("  kMath");
                }
                if(u == 7) {
                  write("  kEnglish");
                }
                write(" Student", s);
              }
            }
          }
          writeln();
        }
      }
    }
    writeln("\n");
  }                  		  

};

execute toukei {
  var y_sum = 0;
  for(var t = 1; t <= teacher; t++) {
    for(var d = 1; d <= date; d++) {
      for(var p = 1; p <= period; p++) {
    	y_sum += y[t][d][p];
      }
    }
  }
  writeln("classes sum:", y_sum);
  
  
  var compatibility = new Array(0,0,0,0,0);
  for(var t = 1; t <= teacher; t++) {
    for(var s = 1; s <= student; s++) {
      for(var u = 1; u <= curriculum; u++) {
    	for(var d = 1; d <= date; d++) {
      	  for(var p = 1; p <= period; p++) {
  			  if(x[t][s][u][d][p] == 1) {
				compatibility[c[s][t]+2] ++;
  			  }
      	  }
		}
      }
    }
  }
  writeln("compatibility");
  for(var i=0; i<5; i++) {
  	writeln("" ,i-2, " : ", compatibility[i] );
  }
    	
  var proficiency = new Array(0,0,0);
  for(var t = 1; t <= teacher; t++) {
    for(var s = 1; s <= student; s++) {
      for(var u = 1; u <= curriculum; u++) {
    	for(var d = 1; d <= date; d++) {
      	  for(var p = 1; p <= period; p++) {
  			  if(x[t][s][u][d][p] == 1) {
				proficiency[h[t][u]] ++;
  			  }
      	  }
		}
      }
    }
  }
  writeln("proficiency");
  for(var i=0; i<=2; i++) {
    writeln("", i, " : ", proficiency[i]);
  }
  
}