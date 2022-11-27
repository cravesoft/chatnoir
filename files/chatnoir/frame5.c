// Action script...

// [Action in Frame 5]
function click_cel(cx, cy)
{
    cel[cy][cx].stat = 2;
    gotoAndPlay("cat");
    all_disable();
} // End of the function
stop ();
cat_position();
all_enable();
