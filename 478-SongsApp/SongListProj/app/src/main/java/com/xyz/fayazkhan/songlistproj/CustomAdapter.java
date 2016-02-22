package com.xyz.fayazkhan.songlistproj;

import android.widget.ArrayAdapter;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.app.Activity;


import java.util.Objects;

/**
 * Created by FayazKhan on 2/21/16.
 */
public class CustomAdapter extends ArrayAdapter<String>
{


    /*
    * Rest of the arrays are not relevant to the operation
    * and not brouught into this class
    * */
    private final Activity context;

    private final String []  artist;
    private final String [] song_name;
    private final int[] song_pic;


    /*Constructor*/
    public CustomAdapter(Activity mainActivity,String[] artist, String[] song_name,int[] song_pic)
    {
        super(mainActivity,R.layout.listitem_main, song_name);

        this.context = mainActivity;
        this.artist = artist;
        this.song_name = song_name;
        this.song_pic = song_pic;

    }

    /*Returning a view object*/
    public View getView(int position, View v, ViewGroup vg)
    {
        LayoutInflater inflater = context.getLayoutInflater();
        View r_view = inflater.inflate(R.layout.listitem_main, null, true);

        TextView name_song_view = (TextView) r_view.findViewById(R.id.l_text);
        TextView name_artist_view = (TextView) r_view.findViewById(R.id.sm_text);
        ImageView song_picture = (ImageView) r_view.findViewById(R.id.imageView);

        name_song_view.setText(song_name[position]);
        name_artist_view.setText(artist[position]);
        song_picture.setImageResource(song_pic[position]);

        return  r_view;

    }

}

