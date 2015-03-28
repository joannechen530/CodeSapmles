package ca.ubc.cs.cpsc210.quiz.model;

/**
 * Represents a category of restaurant with name and alias.
 */
public class Category {

    private String name;
    private String alias;

    //Constructor
    public Category(String name, String alias){
        this.name = name;
        this.alias = alias;
    }

    public String getAlias(){
        return alias;
    }

    public String getName(){
        return name;
    }

    @Override
    public String toString(){
        return name;
    }  

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Category category = (Category) o;

        if (alias != null ? !alias.equals(category.alias) : category.alias != null) return false;
        if (name != null ? !name.equals(category.name) : category.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (alias != null ? alias.hashCode() : 0);
        return result;
    }
}
