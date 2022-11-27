// Action script...

// [Action in Frame 21]
function cat_move()
{
    var _loc4 = 34;
    var _loc3 = 26;
    var _loc2 = [1, 5.000000E-001, -5.000000E-001, -1, -5.000000E-001, 5.000000E-001];
    var _loc1 = [0, 1, 1, 0, -1, -1];
    mcCat._x = mcCat._x + _loc4 * _loc2[catdir];
    mcCat._y = mcCat._y + _loc3 * _loc1[catdir];
} // End of the function
stop ();
mcCat.start_run(catdir);
cnt = 0;
onEnterFrame = function ()
{
    ++cnt;
    if (cnt > 50)
    {
        delete onEnterFrame;
        _parent.mcFade.start_fadeout();
    } // end if
};
