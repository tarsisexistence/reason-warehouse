[@react.component]
let make = (~article: Types.article) =>
  <div key={article.id}> <p> {React.string(article.title)} </p> </div>;