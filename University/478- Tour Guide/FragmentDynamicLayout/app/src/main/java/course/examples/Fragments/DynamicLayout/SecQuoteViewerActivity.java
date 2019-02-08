package course.examples.Fragments.DynamicLayout;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.Toast;

import course.examples.Fragments.DynamicLayout.SecTitlesFragment.ListSelectionListener;

/*
* FOR COMMENTS LOOK IN QuoteViewerActivity
*
* */


//Several Activity lifecycle methods are instrumented to emit LogCat output
//so you can follow this class' lifecycle
public class SecQuoteViewerActivity extends Activity implements
		ListSelectionListener {


	public static String[] PhillyTitleArray;
	public static String[] PhillyQuoteArray;

	private final SecQuotesFragment mQuoteFragment = new SecQuotesFragment();
	private FragmentManager mFragmentManager;
	private FrameLayout mTitleFrameLayout, mQuotesFrameLayout;

	private static final int MATCH_PARENT = LinearLayout.LayoutParams.MATCH_PARENT;
	private static final String TAG = "QuoteViewerActivity";

	public boolean portrait = true;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		Log.i(TAG, getClass().getSimpleName() + ":entered onCreate()");

		super.onCreate(savedInstanceState);

		// Get the string arrays with the titles and quotes
		PhillyTitleArray = getResources().getStringArray(R.array.IndyTitles);
		PhillyQuoteArray = getResources().getStringArray(R.array.Indy_URL);


		setContentView(R.layout.main);

		// Get references to the TitleFragment and to the QuotesFragment
		mTitleFrameLayout = (FrameLayout) findViewById(R.id.title_fragment_container);
		mQuotesFrameLayout = (FrameLayout) findViewById(R.id.quote_fragment_container);


		// Get a reference to the FragmentManager
		mFragmentManager = getFragmentManager();

		// Start a new FragmentTransaction
		FragmentTransaction fragmentTransaction = mFragmentManager
				.beginTransaction();

		// Add the TitleFragment to the layout
		fragmentTransaction.add(R.id.title_fragment_container,
				new SecTitlesFragment());
		
		// Commit the FragmentTransaction
		fragmentTransaction.commit();

		// Add a OnBackStackChangedListener to reset the layout when the back stack changes
		mFragmentManager
				.addOnBackStackChangedListener(new FragmentManager.OnBackStackChangedListener() {
					public void onBackStackChanged() {
						setLayout();
					}
				});
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);

		//Log.i("string works correctly", "Success");
		// Checks the orientation of the screen
		if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE)
		{
			portrait = false;
			//Toast.makeText(getApplicationContext(), "false Philly landscape", Toast.LENGTH_SHORT).show();

		} else if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT)
		{
			portrait = true;
			//Toast.makeText(getApplicationContext(), "True Phillyportrait", Toast.LENGTH_SHORT).show();
		}
		setLayout();
	}


	private void setLayout() {

		// Determine whether the QuoteFragment has been added
		if (portrait == true)
		{
			//Toast.makeText(getApplicationContext(), "INDYSet layoutPortrait", Toast.LENGTH_SHORT).show();
			if (!mQuoteFragment.isAdded()) {

				// Make the TitleFragment occupy the entire layout
				mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
						MATCH_PARENT, MATCH_PARENT));
				mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
						MATCH_PARENT));
			} else
			{


				mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
						0, MATCH_PARENT));
				mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(MATCH_PARENT,
						MATCH_PARENT));
			}
		}
		else
		{

			//Toast.makeText(getApplicationContext(), "INDYSet layoutLanscape", Toast.LENGTH_SHORT).show();
			if (!mQuoteFragment.isAdded())
			{

				mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
						MATCH_PARENT, MATCH_PARENT));
				mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
						MATCH_PARENT));
			}
			else
			{

				// Make the TitleLayout take 1/3 of the layout's width
				mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
						MATCH_PARENT, 1f));

				// Make the QuoteLayout take 2/3's of the layout's width
				mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
						MATCH_PARENT, 2f));

			}



		}

	}

	// Called when the user selects an item in the TitlesFragment
	@Override
	public void onListSelection(int index) {

		// If the QuoteFragment has not been added, add it now
		if (!mQuoteFragment.isAdded()) {
		
			// Start a new FragmentTransaction
			FragmentTransaction fragmentTransaction = mFragmentManager
					.beginTransaction();

			// Add the QuoteFragment to the layout
			fragmentTransaction.add(R.id.quote_fragment_container,
					mQuoteFragment);

			// Add this FragmentTransaction to the backstack
			fragmentTransaction.addToBackStack(null);
			
			// Commit the FragmentTransaction
			fragmentTransaction.commit();
			
			// Force Android to execute the committed FragmentTransaction
			mFragmentManager.executePendingTransactions();
		}
		
		if (mQuoteFragment.getShownIndex() != index) {

			// Tell the QuoteFragment to show the quote string at position index
			mQuoteFragment.showQuoteAtIndex(index);
		
		}
	}

	@Override
	protected void onDestroy() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onDestroy()");
		super.onDestroy();
	}

	@Override
	protected void onPause() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onPause()");
		super.onPause();
	}

	@Override
	protected void onRestart() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onRestart()");
		super.onRestart();
	}

	@Override
	protected void onResume() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onResume()");
		super.onResume();
	}

	@Override
	protected void onStart() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onStart()");
		super.onStart();
	}

	@Override
	protected void onStop() {
		Log.i(TAG, getClass().getSimpleName() + ":entered onStop()");
		super.onStop();
	}



	// Create Options Menu
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.top_menu, menu);
		return true;
	}

	// Process clicks on Options Menu items
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
			case R.id.Chi:
				Toast.makeText(getApplicationContext(), "INDYyou've selected Chicago",
						Toast.LENGTH_SHORT).show();
				Intent nextChi = new Intent(SecQuoteViewerActivity.this,QuoteViewerActivity.class);
				startActivity(nextChi);
				return true;
			case R.id.Indy:
				Toast.makeText(getApplicationContext(), "INDYyou've selected Indianapolis",
						Toast.LENGTH_SHORT).show();
				Intent nextIndy = new Intent(SecQuoteViewerActivity.this,SecQuoteViewerActivity.class);
				startActivity(nextIndy);
				return true;
			default:
				return false;
		}
	}

	// Create Context Menu
	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
									ContextMenu.ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, v, menuInfo);
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.context_menu, menu);
	}

}