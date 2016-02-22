package com.xyz.fayazkhan.songlistproj;


import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.app.Activity; // being extended
import android.widget.ListView;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Toast;
import android.view.ContextMenu;
import android.view.MenuInflater;
import android.view.MenuItem;

/*
*
* Many sources have been used for this assignment.
*
* Some portions of code were taken from prof.Buy notes
* Some were heavily researched from the internet and taken
* bits and peices from every where but very much my own
*
* */


public class MainActivity extends Activity
{
    ListView lv;


    /*
    * Created several arrays for the songs and will essentially user
    * a global coiunter to specify the index the array(s)
    *
    * */
    String[] artist = {"PK","Bunty Aur Babli","Yo Yo Honey Singh","Om Shanti Om","Dabangg","Raanjhanaa",
                       "Raanjhanaa"};

    String[] artist_wiki = {"https://en.wikipedia.org/wiki/PK_%28film%29",
                            "https://en.wikipedia.org/wiki/Bunty_Aur_Babli",
                            "https://en.wikipedia.org/wiki/Yo_Yo_Honey_Singh",
                            "https://en.wikipedia.org/wiki/Om_Shanti_Om",
                            "https://en.wikipedia.org/wiki/Dabangg#Soundtrack",
                            "https://en.wikipedia.org/wiki/Raanjhanaa#Soundtrack",
                            "https://en.wikipedia.org/wiki/Raanjhanaa#Soundtrack"};

    String[] song_name = {"Nanga Punga Dost","Kajra Re","Lak 28 Kudi Da","Dard-e-Disco",
                            "Munni Badnaam Hui","Raanjhanaa","Tum Tak"};

    String[] song_wiki = {  "https://en.wikipedia.org/wiki/Nanga_Punga_Dost",
                            "https://en.wikipedia.org/wiki/Kajra_Re",
                            "https://en.wikipedia.org/wiki/Lak_28_Kudi_Da",
                            "https://en.wikipedia.org/wiki/Dard-e-Disco",
                            "https://en.wikipedia.org/wiki/Munni_Badnaam_Hui",
                            "https://en.wikipedia.org/wiki/Raanjhanaa_%28soundtrack%29",
                            "https://en.wikipedia.org/wiki/Raanjhanaa_%28soundtrack%29"};

    String[] youtube = {    "https://www.youtube.com/watch?v=AKKKRw0IW88",
                            "https://www.youtube.com/watch?v=DovUEruZ2q4",
                            "https://www.youtube.com/watch?v=mZe1w15P1Pw",
                            "https://www.youtube.com/watch?v=ZrQA-w8s-uc",
                            "https://www.youtube.com/watch?v=Jn5hsfbhWx4",
                            "https://www.youtube.com/watch?v=OsTGp5n6w5E",
                            "https://www.youtube.com/watch?v=k09uvR5eUao"};


    /*
    * Dragged and dropped into folder and all lower cae
    * */
    int [] song_pic = {R.drawable.pk, R.drawable.bb,R.drawable.yoyo,R.drawable.osm, R.drawable.dabaang,
                        R.drawable.rj,R.drawable.tum};

    int count = 0;


    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        lv = (ListView) findViewById(R.id.BigList);

        lv.setAdapter(new CustomAdapter(MainActivity.this,artist,song_name,song_pic));

        /*
        * Will pretty much will always look the same. Int the future can sort of copy
        * and paste
        * */
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                //Toast.makeText(MainActivity.this,"You clicked "+ song_name[position],Toast.LENGTH_SHORT).show();
                //Used toast test to see if click was even working

                Intent browser_win = new Intent(Intent.ACTION_VIEW);
                browser_win.setData(Uri.parse(youtube[position]));
                startActivity(browser_win);
            }
        });


        /*DONT FORGET THIS!!!!!*/
        lv.setLongClickable(true);

        /*Below portion will always almost look the same */
        lv.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                count = position;

                registerForContextMenu(parent);
                openContextMenu(parent);
                return true;
            }
        });

    }



    @Override
    public void onCreateContextMenu(ContextMenu menu,View view, ContextMenu.ContextMenuInfo
                                    cmi)
    {
        super.onCreateContextMenu(menu, view, cmi);
        MenuInflater menuInflater = getMenuInflater();//assist in inflating the menu
        menuInflater.inflate(R.menu.long_click_menu, menu);
        /*Had to create an xml file and place it in a menu folder
        * and essentialy specified it to the folder */
    }


    /*
    *
    * Series of if statement for when the user long clicks and specifies
    * an option
    * */
    @Override
    public boolean onContextItemSelected(MenuItem m_item)
    {
        AdapterView.AdapterContextMenuInfo acm_info = (AdapterView.AdapterContextMenuInfo)
                m_item.getMenuInfo();

        if(m_item.getItemId() == R.id.youtube_v)
        {
            Intent browser_win = new Intent(Intent.ACTION_VIEW);
            browser_win.setData(Uri.parse(youtube[count]));
            startActivity(browser_win);
            return true;
        }

        if(m_item.getItemId() == R.id.song_menu)
        {
            Intent browser_win = new Intent(Intent.ACTION_VIEW);
            browser_win.setData(Uri.parse(song_wiki[count]));
            startActivity(browser_win);
            return true;
        }

        if(m_item.getItemId() == R.id.artist_menu)
        {
            Intent browser_win = new Intent(Intent.ACTION_VIEW);
            browser_win.setData(Uri.parse(artist_wiki[count]));
            startActivity(browser_win);
            return true;
        }

        return super.onContextItemSelected(m_item);



    }

}
