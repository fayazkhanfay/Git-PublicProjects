import { Component, OnInit, Input } from '@angular/core';
import { CategoryService } from 'src/app/category.service';

@Component({
  selector: 'product-filter',
  templateUrl: './product-filter.component.html',
  styleUrls: ['./product-filter.component.css']
})
export class ProductFilterComponent implements OnInit {
  categories$;
  @Input('category') category;//@input is used for bring param from another class via html tag

  constructor(categoryService: CategoryService) {
    this.categories$ = categoryService.getAll();
   }

  ngOnInit() {
  }

}
