package course.examples.Fragments.DynamicLayout;

import android.app.Activity;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
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

import course.examples.Fragments.DynamicLayout.TitlesFragment.ListSelectionListener;


/*
* This is main activity class file QuotesFragment,QuoteViewerActivity, and Titles Fragment
* deal with Chicago. The class files that have "Sec" in front deal with Philly
*
* Sec and non-Sec class files are very similar in content but this one has the broadcast receiver
*
* */

//Several Activity lifecycle methods are instrumented to emit LogCat output
//so you can follow this class' lifecycle
public class QuoteViewerActivity extends Activity implements
		ListSelectionListener {

	/*The values for these arrays are in string.xml located in values folder*/
	public static String[] ChiTitleArray;
	public static String[] mQuoteArray;


	private final QuotesFragment mQuoteFragment = new QuotesFragment();
	private FragmentManager mFragmentManager;
	private FrameLayout mTitleFrameLayout, mQuotesFrameLayout;

	private static final int MATCH_PARENT = LinearLayout.LayoutParams.MATCH_PARENT;
	private static final String TAG = "QuoteViewerActivity";

	public boolean portrait = true;


	@Override
	protected void onCreate(Bundle savedInstanceState)
	{


		super.onCreate(savedInstanceState);

		// Get the string arrays with the titles and qutoes
		ChiTitleArray = getResources().getStringArray(R.array.ChiTitles);
		mQuoteArray = getResources().getStringArray(R.array.Chi_URL);

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
				new TitlesFragment());
		
		// Commit the FragmentTransaction
		fragmentTransaction.commit();

		// Add a OnBackStackChangedListener to reset the layout when the back stack changes
		mFragmentManager
				.addOnBackStackChangedListener(new FragmentManager.OnBackStackChangedListener() {
					public void onBackStackChanged() {
						setLayout();
					}
				});


		/***BROADCAST******/
		BroadcastReceiver receiver = new Receiver();

	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);

		/*Checks if screen is in portrait or landscape view and updates the
		 * boolean value accordingly. The portrait boolean is used in setLayout
		 *
		 * */
		// Checks the orientation of the screen
		if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE)
		{
			portrait = false;
			//Toast.makeText(getApplicationContext(), "landscape", Toast.LENGTH_SHORT).show();

		} else if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT)
		{
			portrait = true;
			//Toast.makeText(getApplicationContext(), "portrait", Toast.LENGTH_SHORT).show();
		}
		setLayout();
	}


	private void setLayout() {

		// Determine whether the QuoteFragment has been added
		if (portrait == true)
		{
			//Toast.makeText(getApplicationContext(), "In SetLayout Portrait",
			// Toast.LENGTH_SHORT).show();

			if (!mQuoteFragment.isAdded())
			{

				// Fragment not yet created but is portrait

				// Make the TitleFragment occupy the entire layout

				//Only titles is visible and mQuotes is set to 0 or hidden
				mTitleFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(
						MATCH_PARENT, MATCH_PARENT));
				mQuotesFrameLayout.setLayoutParams(new LinearLayout.LayoutParams(0,
						MATCH_PARENT));
			} else
			{
				//User clicks on title and new activity comes in front of titles
				// Fragment created and is portrait
				//Only mQuotes is visible and titles is set to 0 or hidden
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


	/*BELOW THIS IS ALL FOR OPTIONS MENU*/

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
				//Toast.makeText(getApplicationContext(), "you've selected Chicago",
				//		Toast.LENGTH_SHORT).show();

				//Below class call itself
				Intent nextChi = new Intent(QuoteViewerActivity.this,QuoteViewerActivity.class);
				startActivity(nextChi);
				return true;
			case R.id.Indy:
				//Toast.makeText(getApplicationContext(), "you've selected Philly",
				//		Toast.LENGTH_SHORT).show();

				//below call all the class's related to Philly
				Intent nextPhilly = new Intent(QuoteViewerActivity.this,SecQuoteViewerActivity.class);
				startActivity(nextPhilly);
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