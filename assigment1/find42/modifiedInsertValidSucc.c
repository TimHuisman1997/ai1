Fringe insertValidSucc(Fringe fringe, Fringe prSt, int value) {
  State s;
  if ((value < 0) || (value > RANGE)) {
    /* ignore states that are out of bounds */
    return fringe;
  }
  for(int i = 0; i < prSt.insertCnt; i++){
	  if(value == prSt.states[i].value){
		  /* ignore states that are already visited */
		  return fringe;
	  }
  }
  
  s.value = value;
  return insertFringe(fringe, s);
}
