// Action script...

// [Action in Frame 27]
stop ();
mcCat.mc.gotoAndStop(2);
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
