import { Component, OnInit, OnDestroy } from '@angular/core';
import { ProductService } from 'src/app/product.service';
import { Subscription } from 'rxjs/Subscription';
import { Product } from 'src/app/models/product';
import { DataTableResource } from 'angular5-data-table';

@Component({
  selector: 'app-admin-products',
  templateUrl: './admin-products.component.html',
  styleUrls: ['./admin-products.component.css']
})
export class AdminProductsComponent implements OnInit, OnDestroy{
  products: Product[]; //interface for documenting and compile time checking
  subscription: Subscription;
  tableResource: DataTableResource<Product>
  items: Product[] = [];
  itemCount: number;
  
  /* constructor(private productService: ProductService) {
    //not going to unsubscribe because user may have multiple windows open and want to reflect changes
    this.subscription = this.productService.getAll().
    subscribe(products => this.filteredProducts = this.products = products);
    //First getting all products and having copy then filtering  
   } */

   //For new Table: Need to pass products to tableResource for new table
   constructor(private productService: ProductService) {
    //not going to unsubscribe because user may have multiple windows open and want to reflect changes
    this.subscription = this.productService.getAll().
    subscribe(products => {
      this.products = products;
      this.initializeTable(products);
      
    });
    //First getting all products and having copy then filtering  
   }

   private initializeTable(products: Product[]){
    this.tableResource = new DataTableResource(products);
    this.tableResource.query({offset: 0}) //offset is for starting with first pg
      .then(items => this.items = items)

    this.tableResource.count() //return a promise
      .then(count => this.itemCount = count);
   }

   
   reloadItems(params){
     //when reloadItems is called immediatly but will have delay because tableResource may not be initialized yet
     //will result in a delay. the If condition resolves that issue
    if(!this.tableResource) return;

     //copy and pasted from initializeTable
    this.tableResource.query(params) 
    .then(items => this.items = items)
   }


   //cannont filter on type observable 
  filter(query: string){
    //for case sensitivity convert everything to lower case
    //Since product size are small will filter on the client and not in database
    let filteredProducts = (query) ?
      this.products.filter(p => p.title.toLowerCase().includes(query.toLowerCase())) : 
      this.products; //if user empties input field then returns untouched array of products

    //After filtering need to update datatable resource object
    this.initializeTable(filteredProducts);
  }

  ngOnDestroy(){
    this.subscription.unsubscribe();
  }

  ngOnInit() {
  }

}
