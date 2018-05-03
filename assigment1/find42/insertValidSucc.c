Fringe insertValidSucc(Fringe fringe, Fringe prSt, int value) {
  State s;
  if ((value < 0) || (value > RANGE)) {
    /* ignore states that are out of bounds */
    return fringe;
  }
  
  s.value = value;
  return insertFringe(fringe, s);
}
