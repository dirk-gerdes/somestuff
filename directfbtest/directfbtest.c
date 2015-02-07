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

char text[255];

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

int main (int argc, char **argv)
{

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

  DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
  


	IDirectFBEventBuffer *ev_buf;

	DFBCHECK( dfb->CreateInputEventBuffer( dfb, DICAPS_AXES|DICAPS_BUTTONS|DICAPS_KEYS, DFB_TRUE, &ev_buf));



int k=0;
for( k=0;k<5;k++)
{
DFBCHECK (primary->SetColor (primary, 0x00, 0x00, 0x00, 0xff));
  DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width, screen_height));
	int i;
	for( i=12; i< screen_height; i+=16)
{
	DFBEvent ev;
	



	
	ev_buf->WaitForEvent(ev_buf);
	//if( ev_buf->HasEvent( ev_buf) == DFB_TRUE)
	{
		//b=1;
		ev_buf->GetEvent( ev_buf, &ev);
	
		sprintf( text, "-");

		if( ev.clazz== DFEC_INPUT)
		{
			switch( ev.input.type)
			{
				case DIET_UNKNOWN:
					x=-1;y=-1 ;b=-1;
					break;
				case DIET_KEYPRESS:
				case DIET_KEYRELEASE:
					break;
				case DIET_BUTTONPRESS:
				case DIET_BUTTONRELEASE:
					b= ev.input.buttons;
					break;
				case DIET_AXISMOTION:
					sprintf( text, "%i   -- %i  %i-%i  : %i  ", ev.input.device_id, ev.input.axis, ev.input.min, ev.input.max, ev.input.axisabs);
					if( ev.input.axis==DIAI_X)
					{
						x=ev.input.axisabs;
						max_x=ev.input.max;
						min_x = ev.input.min;
					}
					else if( ev.input.axis==DIAI_Y)
					{
						y=ev.input.axisabs;
						max_y=ev.input.max;
						min_y=ev.input.min;
					}
				break;	

			}
			//if( ev.input.


		}
		//else b=9;
	}

	if( b)
	{
 		DFBCHECK (primary->SetColor (primary, 0xff, 0x00, 0x00, 0xff));
  	}
	else
	{
 		DFBCHECK (primary->SetColor (primary, 0x00, 0xff, 0x00, 0xff));
	}

	DFBCHECK (primary->DrawLine (primary,
			                      0, screen_height / 2,
			       screen_width - 1, screen_height / 2));

	//sprintf( text, "(%i, %i, %x)- %i  X(%i-%i) - Y(%i-%i) ", x, y, b, ev.input.type, min_x, max_x, min_y, max_y);
//	sprintf( text, "(%i)", ev.input.axis);
	//max_x, min_x);

	
	
	DFBCHECK( primary->DrawString( primary, text, -1, 0, i, DSTF_LEFT));
	 DFBCHECK (primary->Flip (primary, NULL, 0));
	 //DFBCHECK (primary->Flip (primary, NULL, 0));

}//for
}//for 
//FBCHECK (primary->Flip (primary, NULL, 0));


  sleep (5);

  primary->Release( primary );
  dfb->Release( dfb );


  return 23;
}

