loop
  If button was just pressed
    begin shutdownCount
    begin blankingCount
    reset OD history
    Set blank to 0
    Displaying blanking code
  If blanking period just ended
    Calculate blank OD
    Set blank
    reset OD history
  If active
    Record an OD
  If active and not blanking
    Calculate time averaged OD
    Display time averaged OD
  Decrement blanking count
  Decrement shutdown count
  delay