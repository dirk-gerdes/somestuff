#include <stdio.h>
#include <unistd.h>



#include <directfb.h>



static IDirectFB *dfb = NULL;

static IDirectFBSurface *primary = NULL;

static int screen_width  = 0;
static int screen_height = 0;


int x=0, y=0, b=0;
int max_x=0, max_y=0;
int min_x=0, min_y=0;

char text[1024];

#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

static IDirectFBFont *font = NULL;


int AnalyseInputEvent( DFBInputEvent *ev, char*msg, int maxlen)
{
	int retval = 1;
	if( !ev || !msg)
		return -1;
	memset (msg, maxlen, 0);
	char temp[512];
	memset( temp, 0, sizeof( temp));

	sprintf( temp, "0x%02X) ", ev->device_id);
	strcat( msg, temp);

	switch (ev->type)
	{
		case DIET_UNKNOWN:
			strncat( msg, "unknown         ", maxlen-strlen(msg));
			break;
		case DIET_KEYPRESS:
			strncat( msg, "keypress        ", maxlen-strlen(msg));
			break;
		case DIET_KEYRELEASE:
			strncat( msg, "keyrelease      ", maxlen-strlen(msg));
			break;
		case DIET_BUTTONPRESS:
			strncat( msg, "buttonpress     ", maxlen-strlen(msg));
			break;
		case DIET_BUTTONRELEASE:
			strncat( msg, "buttonrelease   ", maxlen-strlen(msg));
			break;
		case DIET_AXISMOTION:
			strncat( msg, "axismotion      ", maxlen-strlen(msg));
			break;
		default:
			strncat( msg, "none            ", maxlen-strlen(msg));
			break;

	}

	sprintf( temp, "0x%X " ,ev->flags);
	strncat( msg, temp, maxlen-strlen(msg));

	strncat( msg, "(", maxlen-strlen(msg));
	if( ev->flags ==0)
		strncat( msg, "none", maxlen-strlen(msg));
	if( ev->flags & DIEF_TIMESTAMP)
		strncat( msg, "Timestamp|", maxlen-strlen(msg));
	if( ev->flags & DIEF_AXISABS)
		strncat( msg, "axisabs|", maxlen-strlen(msg));
	if( ev->flags & DIEF_AXISREL)
		strncat( msg, "axisrel|", maxlen-strlen(msg));
	if( ev->flags & DIEF_KEYCODE)
		strncat( msg, "keycode|", maxlen-strlen(msg));
	if( ev->flags & DIEF_KEYID)
		strncat( msg, "keyid|", maxlen-strlen(msg));
	if( ev->flags & DIEF_KEYSYMBOL)
		strncat( msg, "keysymbol|", maxlen-strlen(msg));
	if( ev->flags & DIEF_MODIFIERS)
		strncat( msg, "modifiers|", maxlen-strlen(msg));
	if( ev->flags & DIEF_LOCKS)
		strncat( msg, "locks|", maxlen-strlen(msg));
	if( ev->flags & DIEF_BUTTONS)
		strncat( msg, "buttons|", maxlen-strlen(msg));
	if( ev->flags & DIEF_GLOBAL)
		strncat( msg, "global|", maxlen-strlen(msg));
	if( ev->flags & DIEF_REPEAT)
		strncat( msg, "repeat|", maxlen-strlen(msg));
	if( ev->flags & DIEF_FOLLOW)
		strncat( msg, "follow|", maxlen-strlen(msg));
	if( ev->flags & DIEF_MIN)
		strncat( msg, "min|", maxlen-strlen(msg));
	if( ev->flags & DIEF_MAX)
		strncat( msg, "max|", maxlen-strlen(msg));


	strncat( msg, ")", maxlen-strlen(msg));

	if( ev->flags & DIEF_TIMESTAMP)
		sprintf( temp, "t=(%i:%i)", ev->timestamp.tv_sec, ev->timestamp.tv_usec);
		strncat( msg, temp, maxlen-strlen( msg));


	if( ev->flags & DIEF_AXISREL)
	{
		if( ev->axis == DIAI_X)
			strncat( msg, "x-> ", maxlen-strlen(msg));
		else if(ev->axis == DIAI_Y)
			strncat( msg, "y-> ", maxlen-strlen( msg));
		sprintf( temp, "%i", ev->axisrel);
		strncat( msg, temp, maxlen-strlen(msg));
	}
	if( ev->flags & DIEF_AXISABS)
	{
		if( ev->axis == DIAI_X)
			strncat( msg, "x= ", maxlen-strlen(msg));
		else if(ev->axis == DIAI_Y)
			strncat( msg, "y= ", maxlen-strlen( msg));
		sprintf( temp, "%i", ev->axisabs);
		strncat( msg, temp, maxlen-strlen(msg));
	}

	sprintf( temp, " b(0x%X) ", ev->buttons);
	strncat ( msg,  temp, maxlen-strlen( msg));


	if( ev->type== DIET_BUTTONPRESS)
	{
		sprintf( temp, " Bp(0x%X) ", ev->button);
		strncat ( msg,  temp, maxlen-strlen( msg));
	}
	if( ev->type== DIET_BUTTONRELEASE)
	{
		sprintf( temp, " Br(0x%X) ", ev->button);
		strncat ( msg,  temp, maxlen-strlen( msg));
	}
	
	if( ev->type== DIET_KEYPRESS)
	{
		sprintf( temp, "Key=0x%X", ev->key_code);
		strncat ( msg,  temp, maxlen-strlen( msg));
		if( ev->key_code == 0x01)
			retval=0;	
	}


	return retval;
};


int main (int argc, char **argv)
{
	int run = 1;
	DFBSurfaceDescription dsc;

  	DFBCHECK (DirectFBInit (&argc, &argv));

  	DFBCHECK (DirectFBCreate (&dfb));

 	// DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));

	dsc.flags = DSDESC_CAPS;
	dsc.caps  = DSCAPS_PRIMARY;// | DSCAPS_FLIPPING;

 	DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));

	DFBFontDescription font_dsc;
	
	font_dsc.flags = DFDESC_HEIGHT;
	font_dsc.height = 16;
	DFBCHECK( dfb->CreateFont(dfb, "./decker.ttf", &font_dsc, &font));
	DFBCHECK( primary->SetFont( primary, font));

	DFBCHECK( primary->GetSize( primary, &screen_width, &screen_height));

	IDirectFBEventBuffer *ev_buf;

	DFBCHECK( dfb->CreateInputEventBuffer( dfb, DICAPS_AXES|DICAPS_BUTTONS|DICAPS_KEYS, DFB_TRUE, &ev_buf));

	int k=0;
	do
	{
		DFBCHECK (primary->SetColor (primary, 0x00, 0x00, 0x00, 0xff));
  		DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width, screen_height));
		int i;

		for( i=12; i< screen_height, run==1; i+=14)
		{
			DFBEvent ev;
			memset(text, 0, sizeof(text));	
			ev_buf->WaitForEvent(ev_buf);
			ev_buf->GetEvent( ev_buf, &ev);
	

			if( ev.clazz== DFEC_INPUT)
			{
				run = AnalyseInputEvent(&ev.input, text, sizeof(text));
			}//if DFEC_INPUT
			if( 1)
			{
 				DFBCHECK (primary->SetColor (primary, 0xff, 0x00, 0x00, 0xff));
  			}
			else
			{	
 				DFBCHECK (primary->SetColor (primary, 0x00, 0xff, 0x00, 0xff));
			}	

			DFBCHECK( primary->DrawString( primary, text, -1, 0, i, DSTF_LEFT));
	 		DFBCHECK (primary->Flip (primary, NULL, 0));
	 		//DFBCHECK (primary->Flip (primary, NULL, 0));
		}//for i	
	}while( run);	


	sleep (5);

  	primary->Release( primary );
  	dfb->Release( dfb );
	font->Release( font);

  	return 0;
}

